#ifndef TERM_C
#define TERM_C

#include "term.h"

Term *newTerm(int width) {
    TTF_Font* font = TTF_OpenFont("./media/FIXED_V0.TTF", 8);
    Term *term = (Term*)malloc(sizeof(Term));
    term->font = font;    
    term->linesShown = 20;
    term->curLine = 0;
    term->width = width;

    for (int i=0; i<TERM_MAX_LINES; i++) term->lines[i] = "";
    return term;
}

void termSetLinesShown(Term *term, int linesShown) {
    term->linesShown = linesShown;
}

void termFree(Term *term) {
    if (term != NULL) {
        TTF_CloseFont(term->font);
        free(term);
    }
}

void termPut(Term *term, const char *line) {
    // ring buffer
    term->lines[term->curLine % TERM_MAX_LINES] = line;
    printf("! %s\n", term->lines[term->curLine % TERM_MAX_LINES]);
    term->curLine++;
}

void termRender(Term *term, SDL_Renderer *renderer) {
    SDL_Color white = {255, 255, 255};

    SDL_Surface* surfaceTxt = TTF_RenderText_Solid(term->font, "ASDFASDF", white);
    SDL_Texture* msg = SDL_CreateTextureFromSurface(renderer, surfaceTxt);
    
    int msgW, msgH;
    SDL_QueryTexture(msg, NULL, NULL, &msgW, &msgH);
    
    SDL_Rect msgRect = { 100, 100, msgW, msgH };
    SDL_RenderCopy(renderer, msg, NULL, &msgRect);

    SDL_FreeSurface(surfaceTxt);
    SDL_DestroyTexture(msg);


    
    // for (int lineNum=0; lineNum<1; lineNum++) {
    //     SDL_Surface* surfaceTxt = TTF_RenderText_Solid(term->font, term->lines[lineNum], white);
    //     SDL_Texture* line = SDL_CreateTextureFromSurface(renderer, surfaceTxt);
    //     printf("] %s\n", term->lines[lineNum]);
    
    //     int lineW, lineH;
    //     SDL_QueryTexture(line, NULL, NULL, &lineW, &lineH);
        
    //     // SDL_Rect msgRect = { 5, lineNum*14, lineW, lineH };
    //     SDL_Rect msgRect = { 100, 100, 100, 100}; //lineW, lineH };
    //     SDL_RenderCopy(renderer, line, NULL, &msgRect);
        
    //     SDL_FreeSurface(surfaceTxt);
    //     SDL_DestroyTexture(line);
    //     break;
    // }    
}


#endif // TERM_C


