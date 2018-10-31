#ifndef TERM_H
#define TERM_H

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
#include <string.h>

#include "atlas.h"

#define TERM_MAX_LINES 10000

// TODO introduce cursor position.
// TODO introduce cmd line apart from other lines. nb. only the cmd line is editable.

typedef struct Term {
    SDL_Window* window; // for dimensions
    Atlas* atlas;
    char* lines[TERM_MAX_LINES]; // this should be an array of linked lists.
    int curLine;
    int numCols, numRows;
    int lineHeight, colWidth;
    int top, left;
    bool focus;
    // ---------------------------------------------------------------------------------------------
    // SDL Surfaces
    
} Term;

Term *newTerm(SDL_Window* window, Atlas* atlas, int left, int top, int columns, int rows);
void termSetNumRows(Term *term, int linesShown);
void termPut(Term *term, const char *line);
void termRender(Term *term, SDL_Renderer *renderer);
int  termLineHeight(Term *term);
bool termContainsPoint(Term *term, Sint32 x, Sint32 y);
bool termProcessEvent(Term*, SDL_Event*);
bool termPushChar(Term *term, char c);
bool termPopChar(Term *term);
void termDoReturn(Term *term);
void termRenderLine(Term *term, SDL_Renderer *renderer, int lineNum, int rowNum);
char *termGetCurLine(Term *term);

void freeTerm(Term *term);



// State diagram for terminal.

// Which states can the terminal be in?

// scrolling
// maybe not necessary
// 









#endif // TERM_H
