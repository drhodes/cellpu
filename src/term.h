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

#define TERM_MAX_LINES 2<<16

typedef struct Term {
    SDL_Window* window; // for dimensions
    TTF_Font *font;  
    char *lines[TERM_MAX_LINES];    
    int curLine;
    int numCols, numRows;
    int lineHeight, colWidth;
    int top, left;

    // ---------------------------------------------------------------------------------------------
    // SDL Surfaces
    
} Term;

Term *newTerm(SDL_Window* window, int left, int top, int columns, int rows);
void termSetNumRows(Term *term, int linesShown);
void termPut(Term *term, const char *line);
void termFree(Term *term);
void termRender(Term *term, SDL_Renderer *renderer);
int  termLineHeight(Term *term);
bool termContainsPoint(Term *term, Sint32 x, Sint32 y);


bool termProcessEvent(Term*, SDL_Event*);


// State diagram for terminal.

// Which states can the terminal be in?

// scrolling
// maybe not necessary
// 









#endif // TERM_H
