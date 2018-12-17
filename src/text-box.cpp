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
#include "text-box.hh"

// +-------------------+
// |                   | line 0
// |                   | line 1
// ~                   ~
// ~                   ~
// |                   | line N
// +-------------------+

TextBox::TextBox(Atlas &atlas, int left, int top, int columns, int rows) :
  m_atlas(atlas)
{
  m_numCols = columns;
  m_numRows = rows;
  
  m_bbox.top = top;
  m_bbox.left = left;
  int promptSize = 2;
  m_bbox.height = m_atlas.surfHeight_ * m_numRows;
  m_bbox.width  = m_atlas.surfWidth_ * (promptSize + m_numCols);
  
  for (int row = 0; row < m_numRows; row++) {
    m_lines.push_back("");
    for (int col = 0; col < m_numCols; col++) {
      m_lines[row].push_back(' ');
    }
  }
}

// TextBox::~TextBox() {
//   cerr << "TextBox is indeed being destroyed" << endl;
// }

// bool setChar(x, y, char c);
// int  getLineHeight();
// void render(SDL_Renderer *renderer);
// void renderBackground(SDL_Renderer *renderer);

bool
TextBox::setChar(int row, int col, char c) {
  if (col >= m_numCols || row >= m_numRows) return false;
  m_lines[row][col] = c;
  return true;
}

bool
TextBox::setRow(int row, string s) {
  if (row >= m_numRows) return false;
  m_lines[row] = s;
  return true;
}

void
TextBox::renderBackground(SDL_Renderer *renderer) {
  SDL_Rect rect = {m_bbox.left, m_bbox.top, m_bbox.width, m_bbox.height};
  SDL_SetRenderDrawColor(renderer, 0x70, 0x70, 0x70, 0x70);
  SDL_RenderFillRect(renderer, &rect);
}


void
TextBox::render() {  
  renderBackground(display::getRenderer());
  int curY = 30;
  int curRow = 0;
  
  for (string str : m_lines) {
    int curX = m_bbox.left;
    int curCol = 0;    
    
    for (char c : str) {
      SDL_Rect msgRect = { curX, curY, m_atlas.surfWidth_, m_atlas.surfHeight_ };
      SDL_Texture* glyph = m_atlas.getGlyph(c);
      nullDieMsg(glyph, "failed to get a glyph in textBoxRender");            
      SDL_RenderCopy(display::getRenderer(), glyph, NULL, &msgRect);
      curX += m_atlas.surfWidth_;
      curCol++;
      if (curCol >= m_numCols) break;
    }    
    curY += m_atlas.surfHeight_;
    curRow++;
    if (curRow >= m_numRows) break;
  }
}


/*
void
TextBox::renderLine(SDL_Renderer *renderer, int lineNum, int rowNum) {
  string str("> ");
  str.append(lines[lineNum]);
        
  int curX = left;
  int curY = top + rowNum * m_atlas.surfHeight_;
    
  for (int i=0; str[i]; i++) {
    SDL_Rect msgRect = { curX, curY, m_atlas.surfWidth_, m_atlas.surfHeight_ };
    SDL_Texture* glyph = m_atlas.getGlyph(str[i]);
    nullDieMsg(glyph, "failed to get a glyph in textBoxRender");            
    SDL_RenderCopy(renderer, glyph, NULL, &msgRect);
    curX += m_atlas.surfWidth_;
  }
}

bool
TextBox::containsPx(Sint32 x, Sint32 y) {    
  BBox bb;
  boundingBox(bb);
  return bb.containsPx(x, y);
}


void
TextBox::setupEvents() {
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
TextBox::doReturn() {
  string line = getCurLine();
  lman.doLine(line);
  put(line);
}

inline string
TextBox::getCurLine() {
  return lines[m_curLine];
}

bool
TextBox::curLineFull() {
  return (int)(getCurLine().length()) >= (numCols - 1);
}

/// returns false when can't append char to current line.
bool
TextBox::pushChar(char c) {
  // if line full return false
  if (!curLineFull()) {
    lines[m_curLine].push_back(c);
    return true;
  }
  return false;
}

void
TextBox::popChar() {
  if (getCurLine().length() > 0)
    lines[m_curLine].pop_back();
}
*/
