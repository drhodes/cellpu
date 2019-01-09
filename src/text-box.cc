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
  int border = 1; // px
  int curY = m_bbox.top + border;
  int curRow = 0;
  
  for (string str : m_lines) {
    int curX = m_bbox.left + border;
    int curCol = 0;    
    
    for (char c : str) {
      SDL_Rect msgRect = { curX, curY, m_atlas.surfWidth_, m_atlas.surfHeight_ };
      optional<SDL_Texture*> glyph = m_atlas.getGlyph(c);
      if (glyph.has_value()) {
        SDL_RenderCopy(display::getRenderer(), glyph.value(), NULL, &msgRect);
        curX += m_atlas.surfWidth_;
        curCol++;
      } else {
        terr("failed to get a glyph in textBoxRender");         
      }
      if (curCol >= m_numCols) break;
    }    
    curY += m_atlas.surfHeight_;
    curRow++;
    if (curRow >= m_numRows) break;
  }
}

