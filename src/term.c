#ifndef TERM_C
#define TERM_C

#include <SDL2/SDL_ttf.h>
#include "term.h"
#include "err.h"

Term *newTerm(SDL_Window* window, int width) {
    TTF_Font* font = TTF_OpenFont("./media/Inconsolata-g.ttf", 18);
    nullDie(font);
    TTF_SetFontHinting(font, TTF_HINTING_LIGHT);
    
    Term *term = (Term*)malloc(sizeof(Term));
    nullDie(term);
    term->window = window;
    term->font = font;    
    term->linesShown = 20;
    term->curLine = 0;
    term->width = width;

    for (int i=0; i<TERM_MAX_LINES; i++) {
        term->lines[i] = (char*)malloc(sizeof(char)*term->width);
    }
    return term;
}

void termSetLinesShown(Term *term, int linesShown) {
    term->linesShown = linesShown;
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

void termPut(Term *term, const char *line) {
    // ring buffer    
    char *curLine = term->lines[term->curLine];
    strncpy(curLine, line, 255);
    printf("! %s\n", term->lines[term->curLine]);
    term->curLine += 1;
}

void termRender(Term *term, SDL_Renderer *renderer) {
    
    SDL_Color white = {255, 255, 255, 255};
    int winW, winH;
    SDL_GetWindowSize(term->window, &winW, &winH);
    
    SDL_Surface* surfaceTxt;
    SDL_Texture* line; 

    int stop = term->curLine;
    int start = stop - term->linesShown;
    start = start < 0 ? 0 : start;

    int MARGIN = 5;
    int curY = winH - MARGIN;
    
    for (int lineNum=start; lineNum <= stop; lineNum++) {
        printf("asdf\n");
        char str[300] = "> ";
        strcat(str, term->lines[lineNum]);         
        surfaceTxt = TTF_RenderText_Blended(term->font, str, white);
        line = SDL_CreateTextureFromSurface(renderer, surfaceTxt);
        
        int lineW, lineH;
        SDL_QueryTexture(line, NULL, NULL, &lineW, &lineH);
        curY -= lineH;
        SDL_Rect msgRect = { MARGIN, curY, lineW, lineH };
        SDL_RenderCopy(renderer, line, NULL, &msgRect);
    }
    
    SDL_FreeSurface(surfaceTxt);
    SDL_DestroyTexture(line);

}


#endif // TERM_C


