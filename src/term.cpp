#include <stdbool.h>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>

#include "bbox.h"
#include "err.h"
#include "term.h"
#include "atlas.h"
#include "common.h"

extern lua_State* _LS; // from main.c


Term::Term(SDL_Window* window, Atlas* atlas, int left, int top, int columns, int rows) {
  this->window = window;
  this->atlas = atlas;
  this->curLine = 0;
  this->numCols = columns;
  this->numRows = rows;
  this->top = top;
  this->left = left;
}

Term::~Term() {
  cerr << "Term is indeed being destroyed" << endl;
}


// void
// termSetNumRows(int numRows) {
//     nullDie(term);
//     term->numRows = numRows;
// }

// void
// freeTerm(Term *term) {
//     if (term != NULL) {
//         free(term);
//         for (int i=0; i<TERM_MAX_LINES; i++) {
//             free(term->lines[i]);
//         }
//         // TODO free SDL surfaces. Which surfaces? 
//     }
//     term = NULL;    
// }

// void
// termPut(const char *str) {
//     nullDie(term);
//     // ring buffer
//     // TODO fix mod calculation, why was it failing?
//     assert(term->curLine < TERM_MAX_LINES);
//     char *line = termGetCurLine(term);

//     if (str != line) {
//         // if these are the same strings, then nothing need be copied.
//         strncpy(line, str, term->numCols);
//     }
//     term->curLine += 1;
// }

void
Term::put(string str) {
  assert(curLine < TERM_MAX_LINES);
  lines[curLine] = str;
  curLine += 1;
}

BBox*
Term::boundingBox() {
  BBox *bb = new BBox;
  int promptSize = 2; // TODO consider custom prompt.
  bb->top = top;
  bb->left = left;
  bb->height = atlas->surfHeight_ * (numRows + 1);
  bb->width  = atlas->surfWidth_ * (promptSize + numCols);
  return bb;
}

void
Term::renderCursor(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  string line = getCurLine();
  int curCol = line.length();
  int promptSize = 2; // TODO consider custom prompt.
  int x = left + ((promptSize + curCol) * atlas->surfWidth_);
  int y = top;

  if (curLine >= numRows) {
    // when the cursor hits the bottom of the terminal.
    y += numRows * atlas->surfHeight_;
  } else {
    y += curLine * atlas->surfHeight_;
  }
    
  SDL_Rect rect = { x, y, atlas->surfWidth_, atlas->surfHeight_ };
  
  // Blink
  if (oddSecond()) SDL_RenderFillRect(renderer, &rect); 
}

void
Term::renderBackground(SDL_Renderer *renderer) {
  BBox *bb = boundingBox();
  SDL_Rect rect = {bb->left, bb->top, bb->width, bb->height};
  
  if (focus) {
    SDL_SetRenderDrawColor(renderer, 0x60, 0x35, 0x6A, 0x70);
  } else {
    SDL_SetRenderDrawColor(renderer, 0x45, 0x45, 0x45, 0x20);
  }
  SDL_RenderFillRect(renderer, &rect);
}

void
Term::render(SDL_Renderer *renderer) {
  renderBackground(renderer);
  if (focus) renderCursor(renderer);
    
  int winW, winH;
  SDL_GetWindowSize(window, &winW, &winH);

  int bottomLine = curLine;
  int topLine = bottomLine - numRows;
  if (topLine < 0) topLine = 0;
    
  int rowNum = 0;
  for (int lineNum=topLine; lineNum <= bottomLine; lineNum++) {
    renderLine(renderer, lineNum, rowNum);
    rowNum += 1;
  }
}

void
Term::renderLine(SDL_Renderer *renderer, int lineNum, int rowNum) {
  string str("> ");
  str.append(lines[lineNum]);
  //strncat(str, term->lines[lineNum], term->numCols-2);
        
  int curX = left;
  int curY = top + rowNum * atlas->surfHeight_;
    
  for (int i=0; str[i]; i++) {
      SDL_Rect msgRect = { curX, curY, atlas->surfWidth_, atlas->surfHeight_ };
      SDL_Texture* glyph = atlas->getGlyph(str[i]);
      nullDieMsg(glyph, "failed to get a glyph in termRender");            
      SDL_RenderCopy(renderer, glyph, NULL, &msgRect);
      curX += atlas->surfWidth_;
  }
}

bool
Term::containsPx(Sint32 x, Sint32 y) {    
  BBox *bb = this->boundingBox();
  bool hasPx = bb->containsPx(x, y);
  delete bb;
  return hasPx;
}

bool
Term::processEvent(SDL_Event* ev) {
  // hack together some spaghetti state handling and then build a
  // state machine. Either the terminal has focus or it doesn't. 
  switch (ev->type) {
  case SDL_MOUSEMOTION: {
    Sint32 x = ev->motion.x;
    Sint32 y = ev->motion.y;        
    this->focus = containsPx(x, y);
    break;
  }
    
  case SDL_TEXTINPUT: {
    if (this->focus) pushChar(ev->window.event);
    break;
  }
        
  case SDL_KEYDOWN: {
    if (!this->focus) break;
        
    switch (ev->key.keysym.scancode) {
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
  }
        
  default: {
    //die("Unhandled event in termProcessEvent");
  }}
  return true;
}

void
Term::doReturn() {
  string line = getCurLine();
  int err = luaL_loadbuffer(_LS, line.c_str(), line.length(), "line") || lua_pcall(_LS, 0, 0, 0);
  
  if (err) {
    string errStr(lua_tostring(_LS, -1));
    fprintf(stderr, "%s\n", lua_tostring(_LS, -1));
    perr(errStr);
    lua_pop(_LS, 1);
  }
  
  put(line);
}

inline string
Term::getCurLine() {
  return lines[curLine];
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
    lines[curLine].push_back(c);
    return true;
  }
  return false;
}

void
Term::popChar() {
  lines[curLine].pop_back();
}

/*
  void termDoLineInput(Term *term) {
          
  if (eof == NULL) break;
    
  // directives.
  if (strncmp(buff, "quit", 4) == 0) {
  //     break;
  //  }
          
  // if (strncmp(buff, "reload", 6) == 0) { 
  //     doFile(L, "lua/cell.lua");
  //     doFile(L, "lua/display.lua");            
  //     doFile(L, "lua/grid.lua");
  //     doFile(L, "lua/instructions.lua");
  //     doFile(L, "lua/startup.lua");
  //     continue;
  //  }
        
  // if (strncmp(buff, "help", 4) == 0 || strncmp(buff, "h\n", 2) == 0) {
  //     doFile(L, "lua/help.lua");            
  //     continue;
  //  }
        
  // int err = luaL_loadbuffer(L, buff, strlen(buff), "line") || lua_pcall(L, 0, 0, 0);        
  // if (err) {
  //     fprintf(stderr, "%s\n", lua_tostring(L, -1));
  //     perr(lua_tostring(L, -1));
  //     lua_pop(L, 1);
  //  }
  }
*/



