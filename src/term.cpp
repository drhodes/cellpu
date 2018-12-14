#include <memory>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>

#include "bbox.hh"
#include "err.hh"
#include "term.hh"
#include "atlas.hh"
#include "common.hh"
#include "lua.hh"
#include "display.hh"
#include "event-handler.hh"

extern LuaMgr lman; // main.c

Term::Term(Atlas& atlas, int left, int top, int columns, int rows) :
  EventHandler(),
  m_atlas(atlas)
{
  m_curLine = 0;
  numCols = columns;
  numRows = rows;
  this->top = top;
  this->left = left;

  setupEvents();
  moveToBottom();
}

Term::~Term() {
  cerr << "Term is indeed being destroyed" << endl;
}

void
Term::moveToBottom() {
  auto win = display::getWindow();
  int w, winHeight;
  SDL_GetWindowSize(win,&w,&winHeight);
  BBox bb;
  boundingBox(bb);
  
  this->top = winHeight - bb.height;
}


void
Term::put(string str) {
  assert(m_curLine < TERM_MAX_LINES);
  lines[m_curLine] = str;
  m_curLine += 1;
}

void
Term::boundingBox(BBox &bb) {
  int promptSize = 2; // TODO consider custom prompt.
  bb.top = top;
  bb.left = left;
  bb.height = m_atlas.surfHeight_ * (numRows + 1);
  bb.width  = m_atlas.surfWidth_ * (promptSize + numCols);
}

void
Term::renderCursor(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  string line = getCurLine();
  int curCol = line.length();
  int promptSize = 2; // TODO consider custom prompt.
  int x = left + ((promptSize + curCol) * m_atlas.surfWidth_);
  int y = top;

  if (m_curLine >= numRows) {
    // when the cursor hits the bottom of the terminal.
    y += numRows * m_atlas.surfHeight_;
  } else {
    y += m_curLine * m_atlas.surfHeight_;
  }
    
  SDL_Rect rect = { x, y, m_atlas.surfWidth_, m_atlas.surfHeight_ };
  
  // Blink
  if (oddSecond()) SDL_RenderFillRect(renderer, &rect); 
}

void
Term::renderBackground(SDL_Renderer *renderer) {
  BBox bb;
  boundingBox(bb);
  SDL_Rect rect = {bb.left, bb.top, bb.width, bb.height};
  
  if (focus) {
    SDL_SetRenderDrawColor(renderer, 0x60, 0x35, 0x6A, 0x70);
  } else {
    SDL_SetRenderDrawColor(renderer, 0x45, 0x45, 0x45, 0x20);
  }
  SDL_RenderFillRect(renderer, &rect);
}

void
Term::renderLine(SDL_Renderer *renderer, int lineNum, int rowNum) {
  string str("> ");
  str.append(lines[lineNum]);
        
  int curX = left;
  int curY = top + rowNum * m_atlas.surfHeight_;
    
  for (int i=0; str[i]; i++) {
    SDL_Rect msgRect = { curX, curY, m_atlas.surfWidth_, m_atlas.surfHeight_ };
    SDL_Texture* glyph = m_atlas.getGlyph(str[i]);
    nullDieMsg(glyph, "failed to get a glyph in termRender");            
    SDL_RenderCopy(renderer, glyph, NULL, &msgRect);
    curX += m_atlas.surfWidth_;
  }
}

void
Term::render(SDL_Renderer *renderer) {
  renderBackground(renderer);
  if (focus) renderCursor(renderer);
    
  int winW, winH;
  SDL_GetWindowSize(display::getWindow(), &winW, &winH);

  int bottomLine = m_curLine;
  int topLine = bottomLine - numRows;
  if (topLine < 0) topLine = 0;
    
  int rowNum = 0;
  for (int lineNum=topLine; lineNum <= bottomLine; lineNum++) {
    renderLine(renderer, lineNum, rowNum);
    rowNum += 1;
  }
}

bool
Term::containsPx(Sint32 x, Sint32 y) {    
  BBox bb;
  boundingBox(bb);
  return bb.containsPx(x, y);
}


void
Term::setupEvents() {
  registerEventHandler(SDL_MOUSEMOTION,                       
                       [&](SDL_Event &ev) {
                         Sint32 x = ev.motion.x;
                         Sint32 y = ev.motion.y;        
                         this->focus = containsPx(x, y);
                       });
  
  registerEventHandler(SDL_TEXTINPUT, 
                       [&](SDL_Event &ev) {
                         if (this->focus) {
                           pushChar(ev.window.event);
                         }
                       });

  registerEventHandler(SDL_KEYDOWN, 
                       [&](SDL_Event &ev) {
                         if (!this->focus) return;                         
                         switch (ev.key.keysym.scancode) {
                           
                         case SDL_SCANCODE_BACKSPACE:
                           popChar();
                           break;
                         case SDL_SCANCODE_RETURN:
                         case SDL_SCANCODE_RETURN2: {
                           doReturn();
                           break;
                         }
                         default:
                           printf("unhandled scan code\n");
                           break;
                         }
                       });
}

void
Term::doReturn() {
  string line = getCurLine();
  lman.doLine(line);
  put(line);
}

inline string
Term::getCurLine() {
  return lines[m_curLine];
}

bool
Term::curLineFull() {
  return (int)(getCurLine().length()) >= (numCols - 1);
}

/// returns false when can't append char to current line.
bool
Term::pushChar(char c) {
  // if line full return false
  if (!curLineFull()) {
    lines[m_curLine].push_back(c);
    return true;
  }
  return false;
}

void
Term::popChar() {
  if (getCurLine().length() > 0)
    lines[m_curLine].pop_back();
}
