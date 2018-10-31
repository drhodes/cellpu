#ifndef TERM_C
#define TERM_C

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

extern lua_State* L; // from main.c

Term*
newTerm(SDL_Window* window, Atlas* atlas, int left, int top, int columns, int rows) {
    nullDie(window); nullDie(atlas);
    
    Term *term = (Term*)malloc(sizeof(Term));
    nullDieMsg(term, "malloc fails allocate memory");
    term->window = window;
    term->atlas = atlas;
    term->curLine = 0;
    term->numCols = columns;
    term->numRows = rows;
    term->top = top;
    term->left = left;

    for (int i=0; i<TERM_MAX_LINES; i++) {
        term->lines[i] = calloc(term->numCols, sizeof(char));
    }
    return term;
}

void
termSetNumRows(Term *term, int numRows) {
    nullDie(term);
    term->numRows = numRows;
}

void
freeTerm(Term *term) {
    if (term != NULL) {
        free(term);
        for (int i=0; i<TERM_MAX_LINES; i++) {
            free(term->lines[i]);
        }
        // TODO free SDL surfaces. Which surfaces? 
    }
    term = NULL;    
}

void
termPut(Term *term, const char *str) {
    nullDie(term);
    // ring buffer
    // TODO fix mod calculation, why was it failing?
    assert(term->curLine < TERM_MAX_LINES);
    char *line = termGetCurLine(term);
    strcpy(line, str);
    term->curLine += 1;
}

void
termBBox(Term *term, BBox *bb) {
    nullDie(term);
    nullDie(bb);
    // including the margin.
    int promptSize = 2; // TODO consider custom prompt.
    bb->top = term->top;
    bb->left = term->left;
    bb->height = term->atlas->surfHeight * (term->numRows + 1);
    bb->width  = term->atlas->surfWidth * (promptSize + term->numCols);
}

void
termRenderCursor(Term *term, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    char *line = termGetCurLine(term);
    int curCol = strlen(line);
    int promptSize = 2; // TODO consider custom prompt.
    int x = term->left + ((promptSize + curCol) * term->atlas->surfWidth);
    int y = term->top;
    
    if (term->curLine >= term->numRows) {
        // when the cursor hits the bottom of the terminal.
        y += term->numRows * term->atlas->surfHeight;
    } else {
        y += term->curLine * term->atlas->surfHeight;
    }
    
    SDL_Rect rect = { x, y, term->atlas->surfWidth, term->atlas->surfHeight };

    // Blink
    if (oddSecond()) SDL_RenderFillRect(renderer, &rect); 
}

void
termRenderBackground(Term *term, SDL_Renderer *renderer) {
    BBox bb;
    termBBox(term, &bb);
    SDL_Rect rect = {bb.left, bb.top, bb.width, bb.height};
    if (term->focus) {
        SDL_SetRenderDrawColor(renderer, 0x60, 0x35, 0x6A, 0x70);
    } else {
        SDL_SetRenderDrawColor(renderer, 0x45, 0x45, 0x45, 0x20);
    }
    SDL_RenderFillRect(renderer, &rect);
}

void
termRender(Term *term, SDL_Renderer *renderer) {
    nullDie(term);
    termRenderBackground(term, renderer);
    if (term->focus) termRenderCursor(term, renderer);
    
    //
    int winW, winH;
    SDL_GetWindowSize(term->window, &winW, &winH);

    int bottomLine = term->curLine;
    int topLine = bottomLine - term->numRows;
    if (topLine < 0) topLine = 0;
    
    int rowNum = 0;
    for (int lineNum=topLine; lineNum <= bottomLine; lineNum++) {
        termRenderLine(term, renderer, lineNum, rowNum);
        rowNum += 1;
    }
}

void
termRenderLine(Term *term, SDL_Renderer *renderer, int lineNum, int rowNum) {
    char str[300] = "> ";
    strncat(str, term->lines[lineNum], term->numCols-2);
        
    int curX = term->left;
    int curY = term->top + rowNum * term->atlas->surfHeight;
    
    for (int i=0; str[i]; i++) {
        SDL_Rect msgRect = { curX, curY, term->atlas->surfWidth, term->atlas->surfHeight };
        SDL_Texture* glyph = atlasGetGlyph(term->atlas, str[i]);
        nullDieMsg(glyph, "failed to get a glyph in termRender");            
        SDL_RenderCopy(renderer, glyph, NULL, &msgRect);
        curX += term->atlas->surfWidth;
    }
}

bool
termContainsPoint(Term *term, Sint32 x, Sint32 y) {    
    nullDie(term);
    BBox bb;
    termBBox(term, &bb);
    return bboxContains(bb, x, y);
}

bool
termProcessEvent(Term* term, SDL_Event* ev) {
    nullDie(term); nullDie(ev);
    
    // hack together some spaghetti state handling and then build a
    // state machine. Either the terminal has focus or it doesn't. 
    switch (ev->type) {
            
    case SDL_MOUSEMOTION: {
        Sint32 x = ev->motion.x;
        Sint32 y = ev->motion.y;        
        term->focus = termContainsPoint(term, x, y);
        break;
    }
    
    case SDL_TEXTINPUT: {
        if (term->focus) termPushChar(term, ev->window.event);
        break;
    }
        
    case SDL_KEYDOWN: {
        if (!term->focus) break;
        
        switch (ev->key.keysym.scancode) {
        case SDL_SCANCODE_BACKSPACE:
            termPopChar(term);
            break;
        case SDL_SCANCODE_RETURN:
        case SDL_SCANCODE_RETURN2: {
            termDoReturn(term);
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
termDoReturn(Term *term) {
    char *line = termGetCurLine(term);
    int err = luaL_loadbuffer(L, line, strlen(line), "line") || lua_pcall(L, 0, 0, 0);
    
    if (err) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        perr(lua_tostring(L, -1));
        lua_pop(L, 1);
    }
            
    termPut(term, line);
}

char*
termGetCurLine(Term *term) {
    return term->lines[term->curLine];
}

static bool
curLineFull(Term *term) {
    return strlen(termGetCurLine(term)) >= term->numCols - 1;
}

/// returns false when can't append char to current line.
bool
termPushChar(Term *term, char c) {
    // if line full return false
    if (!curLineFull(term)) {
        char *line = termGetCurLine(term);    
        int pos = strlen(line);
        line[pos] = c;
        return true;
    }
    return false;
}

bool
termPopChar(Term *term) {
    // if line full return false
    char *line = termGetCurLine(term);
    int pos = strlen(line);
    if (pos > 0) {
        line[pos-1] = '\0';
        return true;
    }
    return false;
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

#endif // TERM_C



