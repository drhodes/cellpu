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

typedef struct {
    // a text buffer
    TTF_Font *font;
    const char *lines[TERM_MAX_LINES];
    int linesShown;
    int curLine;
    int width;
} Term;

Term *newTerm(int width);
void termSetLinesShown(Term *term, int linesShown);
void termPut(Term *term, const char *line);
void termFree(Term *term);
void termRender(Term *term, SDL_Renderer *renderer);
int  termLineHeight(Term *term);

#endif // TERM_H
