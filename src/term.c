#ifndef TERM_C
#define TERM_C

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <stdbool.h> 

#include "bbox.h"
#include "err.h"
#include "term.h"
#include "atlas.h"

Term *newTerm(SDL_Window* window, Atlas* atlas, int left, int top, int columns, int rows) {
    TTF_Font* font = TTF_OpenFont("./media/Inconsolata-g.ttf", 16);
    nullDie(font);
    TTF_SetFontHinting(font, TTF_HINTING_LIGHT);
    
    Term *term = (Term*)malloc(sizeof(Term));
    term->window = window;
    term->atlas = atlas;
    term->font = font;    
    term->curLine = 0;
    term->numCols = columns;
    term->numRows = rows;
    term->top = top;
    term->left = left;

    // if (TTF_SizeText(font, "W", &(term->lineHeight), &(term->colWidth))) {        
    //     perr("Couldn't figure out the font dimensions");
    //     return NULL;
    // }

    //term->lines = (char**)malloc(TERM_MAX_LINES * sizeof(char*));
    for (int i=0; i<TERM_MAX_LINES; i++) {
        int numBytes = sizeof(char) * (term->numCols);
        term->lines[i] = (char*)malloc(numBytes);  
        memset( term->lines[i], '\0', numBytes);
    }
    return term;
}

void termSetNumRows(Term *term, int numRows) {
    nullDie(term);
    term->numRows = numRows;
}

void freeTerm(Term *term) {
    if (term != NULL) {
        TTF_CloseFont(term->font);
        free(term);
        for (int i=0; i<TERM_MAX_LINES; i++) {
            free(term->lines[i]);
        }

        // TODO free SDL surfaces.
    }
    term = NULL;    
}

void termPut(Term *term, const char *str) {
    nullDie(term);
    // ring buffer
    
    // TODO fix mod calculation, why was it failing?
    assert(term->curLine < TERM_MAX_LINES);
    char *line = getCurLine(term);
    strcpy(line, str);
    term->curLine += 1;
}

void termBBox(Term *term, BBox *bb) {
    nullDie(term);
    nullDie(bb);
    // including the margin.
    bb->top = term->top;
    bb->left = term->left;
    bb->height = term->numRows  * term->atlas->surfHeight;
    bb->width  = term->atlas->surfWidth * term->numCols;
}


void renderCursor(Term *term, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    char *line = getCurLine(term);
    int curCol = strlen(line); // magic two because of the ">>" prompt. kind of lame. 
    int x = term->left + ((2 + curCol) * term->atlas->surfWidth);
    int y = term->top + term->curLine * term->atlas->surfHeight;
    SDL_Rect rect = {x, y, term->atlas->surfWidth, term->atlas->surfHeight};
    SDL_RenderFillRect(renderer, &rect);
}

void termRender(Term *term, SDL_Renderer *renderer) {
    nullDie(term);
    // draw a background.
    BBox bb;
    termBBox(term, &bb);
    SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0xff, 0xff);
    SDL_Rect rect = {bb.left, bb.top, bb.width, bb.height};
    SDL_RenderFillRect(renderer, &rect);

    renderCursor(term, renderer);
    
    //
    int winW, winH;
    SDL_GetWindowSize(term->window, &winW, &winH);

    int stop = term->curLine;
    int start = stop - term->numRows;
    start = start < 0 ? 0 : start;

    int curY = term->top;
    
    for (int lineNum=start; lineNum <= stop; lineNum++) {        
        char str[300] = "> ";
        strncat(str, term->lines[lineNum], term->numCols-2);         
        int curX = term->left;
        
        for (int i=0; str[i]; i++) {
            SDL_Rect msgRect = { curX, curY, term->atlas->surfWidth, term->atlas->surfHeight };
            SDL_Texture* glyph = atlasGetGlyph(term->atlas, str[i]);
            SDL_RenderCopy(renderer, glyph, NULL, &msgRect);
            // Why divide by two? Why does newAtlas/renderglyph add extra space?
            curX += term->atlas->surfWidth;
        }
        curY += term->atlas->surfHeight;

    }
}

bool termContainsPoint(Term *term, Sint32 x, Sint32 y) {    
    nullDie(term);
    BBox bb;
    termBBox(term, &bb);
    return bboxContains(bb, x, y);
}

bool termProcessEvent(Term* term, SDL_Event* ev) {
    nullDie(term); nullDie(ev);
    
    // hack together some spaghetti state handling and then build a
    // state machine. Either the terminal has focus or it doesn't. 
    switch (ev->type) {
            
    case SDL_MOUSEMOTION: {
        Sint32 x = ev->motion.x;
        Sint32 y = ev->motion.y;        
        if (termContainsPoint(term, x, y)) {
            printf("termProcessEvent mouse motion %d, %d\n", x, y);
        }
        break;
    }
        
    case SDL_KEYDOWN: {
        switch (ev->key.keysym.scancode) {
        case SDL_SCANCODE_BACKSPACE:
            termPopChar(term);
            break;
        default:
            termPushChar(term, ev->key.keysym.sym);
            break;
        }
    }
        
    default: {
        die("Unhandled event in termProcessEvent");
    }}
    return true;
}


char *getCurLine(Term *term) {
    return term->lines[term->curLine];
}

bool curLineFull(Term *term) {
    return strlen(getCurLine(term)) >= term->numCols - 1;
}


/// returns false when can't append char to current line.
bool termPushChar(Term *term, char c) {
    // if line full return false
    if (!curLineFull(term)) {
        char *line = getCurLine(term);    
        int pos = strlen(line);
        line[pos] = c;
        return true;
    }
    return false;
}

bool termPopChar(Term *term) {
    // if line full return false
    char *line = getCurLine(term);
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




        // SDLK_b: {
        //     } 
        // SDLK_c: {
        //     } 
        // SDLK_d: {
        //     } 
        // SDLK_e: {
        //     } 
        // SDLK_f: {
        //     } 
        // SDLK_g: {
        //     } 
        // SDLK_h: {
        //     } 
        // SDLK_i: {
        //     } 
        // SDLK_j: {
        //     } 
        // SDLK_k: {
        //     } 
        // SDLK_l: {
        //     } 
        // SDLK_m: {
        //     } 
        // SDLK_n: {
        //     } 
        // SDLK_o: {
        //     } 
        // SDLK_p: {
        //     } 
        // SDLK_q: {
        //     } 
        // SDLK_r: {
        //     } 
        // SDLK_s: {
        //     } 
        // SDLK_t: {
        //     } 
        // SDLK_u: {
        //     } 
        // SDLK_v: {
        //     } 
        // SDLK_w: {
        //     } 
        // SDLK_x: {
        //     } 
        // SDLK_y: {
        //     } 
        // SDLK_z: {
        //     } 
