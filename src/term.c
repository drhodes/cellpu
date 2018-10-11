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
    TTF_Font* font = TTF_OpenFont("./media/Inconsolata-g.ttf", 18);
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

    if (TTF_SizeText(font, "W", &(term->lineHeight), &(term->colWidth))) {        
        perr("Couldn't figure out the font dimensions");
        return NULL;
    }
    
    for (int i=0; i<TERM_MAX_LINES; i++) {        
        term->lines[i] = (char*)malloc(sizeof(char)*term->numCols);
        term->lines[i][0] = '\0';
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
    
    char *line = term->lines[term->curLine];
    strncpy(line, str, term->numCols);
    printf("! %s\n", term->lines[term->curLine]);
    term->curLine += 1;
}

void termBBox(Term *term, BBox *bb) {
    nullDie(term);
    nullDie(bb);
    // including the margin.
    bb->top = term->top;
    bb->left = term->left;
    bb->height = term->numRows  * term->atlas->surfHeight;
    bb->width  = term->colWidth * term->numCols;
}

void termRender(Term *term, SDL_Renderer *renderer) {
    nullDie(term);
    // draw a background.
    BBox bb;
    termBBox(term, &bb);
    SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0xff, 0xff);
    SDL_Rect rect = {bb.left, bb.top, bb.width, bb.height};
    SDL_RenderFillRect(renderer, &rect);
    
    //
    int winW, winH;
    SDL_GetWindowSize(term->window, &winW, &winH);

    int stop = term->curLine;
    int start = stop - term->numRows;
    start = start < 0 ? 0 : start;

    int curY = term->top;
    
    for (int lineNum=start; lineNum <= stop; lineNum++) {        
        char str[300] = "> ";
        strcat(str, term->lines[lineNum]);         
        int curX = term->left;

        for (int i=0; str[i]; i += 1) {
            SDL_Rect msgRect = { curX, curY, term->atlas->surfWidth, term->atlas->surfHeight };
            SDL_RenderCopy(renderer, term->atlas->table[str[i]], NULL, &msgRect);
            // Why divide by two? Why does newAtlas/renderglyph add extra space?
            curX += term->colWidth / 2; 
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

// hasFocus
// 

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
    }        
    case SDL_KEYDOWN: {
        ;
    }

    default: {
        //perr("Unhandled event");
        return false;
    }}
    return true;
}


#endif // TERM_C


