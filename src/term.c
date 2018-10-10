#ifndef TERM_C
#define TERM_C

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <stdbool.h> 

#include "bbox.h"
#include "err.h"
#include "term.h"

Term *newTerm(SDL_Window* window, int top, int left, int columns, int rows) {
    TTF_Font* font = TTF_OpenFont("./media/Inconsolata-g.ttf", 18);
    nullDie(font);
    TTF_SetFontHinting(font, TTF_HINTING_LIGHT);
    
    Term *term = (Term*)malloc(sizeof(Term));
    term->window = window;
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
    }
    return term;
}

void termSetNumRows(Term *term, int numRows) {
    nullDie(term);
    term->numRows = numRows;
}

void termFree(Term *term) {
    if (term != NULL) {
        TTF_CloseFont(term->font);
        free(term);
        term = NULL;
        for (int i=0; i<TERM_MAX_LINES; i++) {
            free(term->lines[i]);
        }
    }
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

int TERM_MARGIN = 5;

void termRender(Term *term, SDL_Renderer *renderer) {
    nullDie(term);
    
    SDL_Color white = {255, 255, 255, 255};
    int winW, winH;
    SDL_GetWindowSize(term->window, &winW, &winH);

    int stop = term->curLine;
    int start = stop - term->numRows;
    start = start < 0 ? 0 : start;

    int curY = winH - TERM_MARGIN;
    
    for (int lineNum=stop; lineNum > start; lineNum--) {        
        char str[300] = "> ";
        strcat(str, term->lines[lineNum]);         
        SDL_Surface* surfaceTxt = TTF_RenderText_Blended(term->font, str, white);
        SDL_Texture* line = SDL_CreateTextureFromSurface(renderer, surfaceTxt);
        
        int lineW, lineH;
        SDL_QueryTexture(line, NULL, NULL, &lineW, &lineH);
        curY -= lineH;
        SDL_Rect msgRect = { TERM_MARGIN, curY, lineW, lineH };
        SDL_RenderCopy(renderer, line, NULL, &msgRect);
        
        SDL_FreeSurface(surfaceTxt);
        SDL_DestroyTexture(line);
    }
}

void termBBox(Term *term, BBox *bb) {
    nullDie(term);
    nullDie(bb);
    // including the margin.
    bb->top = term->top;
    bb->left = term->left;
    bb->height = term->numRows  * term->lineHeight + 2*TERM_MARGIN;
    bb->width  = term->colWidth * term->numCols    + 2*TERM_MARGIN;    
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
        // if (termContainsPoint(term, x, y)) {
        printf("termProcessEvent mouse motion %d, %d\n", x, y);
            //}
    }

    case SDL_KEYDOWN: {
        printf("keyboard sym: %s\n");
        if(ev->key.keysym.sym == SDLK_q) exit(0);
    }

    default: {
        //perr("Unhandled event");
        return false;
    }}
    return true;
}


#endif // TERM_C

