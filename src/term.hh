#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <stdbool.h> 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>

#include "atlas.hh"
#include "bbox.hh"
#include "event-handler.hh"
#include "line.hh"

// TODO introduce cursor position.
// TODO introduce cmd line apart from other lines. nb. only the cmd line is editable.

using namespace std;

class Term : public EventHandler {
  static const int TERM_MAX_LINES = 10000;
        
public:
  Atlas& m_atlas = *new Atlas("./media/Terminus.ttf", 16);
  string lines[TERM_MAX_LINES];
  int m_curLine;
  int numCols, numRows;
  int lineHeight, colWidth;
  int top, left;
  bool focus;
  
  Term(int left, int top, int columns, int rows);
  ~Term(); //freeTerm(Term *term);

  bool containsPx(Sint32 x, Sint32 y);
  bool curLineFull();
  bool pushChar(char c);  
  int  getLineHeight();
  string getCurLine();
  void boundingBox(BBox&);
  void doReturn();
  void moveToBottom();
  void popChar();  
  void putInput(string line);
  void render(SDL_Renderer *renderer);
  void renderBackground(SDL_Renderer *renderer);
  void renderCursor(SDL_Renderer *renderer);
  void renderLine(SDL_Renderer *renderer, int lineNum, int rowNum);
  void setNumRows(int linesShown);
  void setupEvents();

};


// State diagram for terminal.
// Which states can the terminal be in?
// scrolling
// maybe not necessary
// 
