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

#include "atlas.hh"
#include "bbox.hh"

// TODO introduce cursor position.
// TODO introduce cmd line apart from other lines. nb. only the cmd line is editable.

using namespace std;

class Term {
  static const int TERM_MAX_LINES = 10000;
        
public:
  shared_ptr<Atlas> m_atlas;
  string lines[TERM_MAX_LINES];
  int curLine;
  int numCols, numRows;
  int lineHeight, colWidth;
  int top, left;
  bool focus;
    
  Term(shared_ptr<Atlas> atlas, int left, int top, int columns, int rows);
  ~Term(); //freeTerm(Term *term);

  void setNumRows(int linesShown);
  void put(string line);
  void render(SDL_Renderer *renderer);
  int  getLineHeight();
  bool containsPx(Sint32 x, Sint32 y);
  bool processEvent(SDL_Event*);
  bool pushChar(char c);  
  bool curLineFull();
  void popChar();  
  void doReturn();
  void renderLine(SDL_Renderer *renderer, int lineNum, int rowNum);
  void renderBackground(SDL_Renderer *renderer);
  void renderCursor(SDL_Renderer *renderer);
  BBox *boundingBox();
  string getCurLine();
};


// State diagram for terminal.
// Which states can the terminal be in?
// scrolling
// maybe not necessary
// 
