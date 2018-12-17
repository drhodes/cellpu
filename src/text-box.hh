#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "atlas.hh"
#include "bbox.hh"

using namespace std;

class TextBox {
public:
  Atlas& m_atlas;
  int m_numCols;
  int m_numRows;
  int m_lineHeightPx;
  int m_colWidthPx;
  vector<string> m_lines;
  BBox m_bbox;
  
  TextBox(Atlas& atlas, int left, int top, int numCols, int numRows);
  
  bool setChar(int x, int y, char c);
  bool setRow(int row, string s);
  int  getLineHeight();
  void render(); 
  void renderBackground(SDL_Renderer *renderer); 
  void moveToBottom();
};


// State diagram for textBoxinal.
// Which states can the textBoxinal be in?
// scrolling
// maybe not necessary
// 
