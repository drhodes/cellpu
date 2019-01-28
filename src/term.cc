#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>

#include "global.hh"
#include "atlas.hh"
#include "bbox.hh"
#include "common.hh"
#include "display.hh"
#include "err.hh"
#include "lua.hh"
#include "term.hh"

Term::Term(int left, int top, int columns, int rows) {
  m_curLine = 0;
  m_numCols = columns;
  m_numRows = rows;
  m_top = top;
  m_left = left;

  moveToBottom();
}

// Term::~Term() { cerr << "Term is indeed being destroyed" << endl; }

void Term::accept(std::shared_ptr<Visitor> v) { v->visit(*this); }

void Term::moveToBottom() {
  auto win = display::getWindow();
  int w, winHeight;
  SDL_GetWindowSize(win, &w, &winHeight);
  BBox bb;
  boundingBox(bb);

  m_top = winHeight - bb.height;
}

void Term::putInput(string str) {
  assert(m_curLine < TERM_MAX_LINES);
  m_lines[m_curLine] = str;
  m_curLine += 1;
}

void Term::boundingBox(BBox &bb) {
  int promptSize = 2;  // TODO consider custom prompt.
  bb.top = m_top;
  bb.left = m_left;
  bb.height = m_atlas.surfHeight_ * (m_numRows + 1);
  bb.width = m_atlas.surfWidth_ * (promptSize + m_numCols);
}

void Term::renderCursor(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  string line = getCurLine();
  int curCol = line.length();
  int promptSize = 2;  // TODO consider custom prompt.
  int x = m_left + ((promptSize + curCol) * m_atlas.surfWidth_);
  int y = m_top;

  if (m_curLine >= m_numRows) {
    // when the cursor hits the bottom of the terminal.
    y += m_numRows * m_atlas.surfHeight_;
  } else {
    y += m_curLine * m_atlas.surfHeight_;
  }

  SDL_Rect rect = {x, y, m_atlas.surfWidth_, m_atlas.surfHeight_};

  // Blink
  if (oddSecond()) SDL_RenderFillRect(renderer, &rect);
}

void Term::renderBackground(SDL_Renderer *renderer) {
  BBox bb;
  boundingBox(bb);
  SDL_Rect rect = {bb.left, bb.top, bb.width, bb.height};

  if (m_focus) {
    SDL_SetRenderDrawColor(renderer, 0x60, 0x35, 0x6A, 0xBB);
  } else {
    SDL_SetRenderDrawColor(renderer, 0x45, 0x45, 0x45, 0xBB);
  }
  SDL_RenderFillRect(renderer, &rect);
}

void Term::renderLine(SDL_Renderer *renderer, int lineNum, int rowNum) {
  string str("> ");
  str.append(m_lines[lineNum]);

  int curX = m_left;
  int curY = m_top + rowNum * m_atlas.surfHeight_;

  for (int i = 0; str[i]; i++) {
    SDL_Rect msgRect = {curX, curY, m_atlas.surfWidth_, m_atlas.surfHeight_};
    optional<SDL_Texture *> glyph = m_atlas.getGlyph(str[i]);

    if (glyph.has_value()) {
      SDL_RenderCopy(renderer, glyph.value(), NULL, &msgRect);
      curX += m_atlas.surfWidth_;
    } else {
      nullDieMsg(nullptr, "failed to get a glyph in Term::renderLine");
    }
  }
}

void Term::render(SDL_Renderer *renderer) {
  renderBackground(renderer);
  if (m_focus) renderCursor(renderer);

  int winW, winH;
  SDL_GetWindowSize(display::getWindow(), &winW, &winH);

  int bottomLine = m_curLine;
  int topLine = bottomLine - m_numRows;
  if (topLine < 0) topLine = 0;

  int rowNum = 0;
  for (int lineNum = topLine; lineNum <= bottomLine; lineNum++) {
    renderLine(renderer, lineNum, rowNum);
    rowNum += 1;
  }
}

bool Term::containsPx(Sint32 x, Sint32 y) {
  BBox bb;
  boundingBox(bb);
  return bb.containsPx(x, y);
}

void Term::updateFocus(SDL_Event &ev) {
  if (ev.type == SDL_MOUSEMOTION) {
    m_focus = containsPx(ev.motion.x, ev.motion.y);
  } else {
    m_focus = false;
  }
}

void Term::doReturn() {
  string line = getCurLine();
  string result = global::lman().doLine(line);
  putInput(line);
  putInput(result);
}

inline string Term::getCurLine() { return m_lines[m_curLine]; }

bool Term::curLineFull() {
  return (int)(getCurLine().length()) >= (m_numCols - 1);
}

/// returns false when can't append char to current line.
bool Term::pushChar(char c) {
  // if line full return false
  if (!curLineFull()) {
    m_lines[m_curLine].push_back(c);
    return true;
  }
  return false;
}

void Term::popChar() {
  if (getCurLine().length() > 0) m_lines[m_curLine].pop_back();
}

void Term::focus(bool f) { m_focus = f; }

bool Term::focus() { return m_focus; }
