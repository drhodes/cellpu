#ifndef ATLAS_C
#define ATLAS_C

#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include "atlas.h"
#include "err.h"

Atlas *newAtlas(SDL_Renderer *renderer) {
    TTF_Font* font = TTF_OpenFont("./media/Inconsolata-g.ttf", 18);
    nullDie(font);
    TTF_SetFontHinting(font, TTF_HINTING_LIGHT);
    SDL_Color white = {255, 255, 255, 255};

    Atlas *atlas = (Atlas*)malloc(sizeof(Atlas));
    
    for (int i=0; i<128; i++) {
        SDL_Surface* surfaceTxt = TTF_RenderGlyph_Blended(font, i, white);
        atlas->table[i] = SDL_CreateTextureFromSurface(renderer, surfaceTxt);
        SDL_QueryTexture(atlas->table[i], NULL, NULL, &atlas->surfWidth, &atlas->surfHeight);
        SDL_FreeSurface(surfaceTxt);
    }
    
    return atlas;
}

void freeAtlas(Atlas *atlas) {
    
}




#endif // ATLAS

