#ifndef ATLAS_C
#define ATLAS_C

#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include "atlas.h"
#include "err.h"

Atlas *newAtlas(SDL_Renderer *renderer, const char *fontFilename, int size) {
    TTF_Font* font = TTF_OpenFont(fontFilename, size);
    nullDie(font);
    TTF_SetFontHinting(font, TTF_HINTING_NONE); //TTF_HINTING_LIGHT);

    SDL_Color white = {255, 255, 255, 255};
    
    Atlas *atlas = (Atlas*)malloc(sizeof(Atlas));
    
    for (int i=0; i<ATLAS_SIZE; i++) {
        SDL_Surface* surfaceTxt = TTF_RenderGlyph_Blended(font, i, white);
        atlas->table[i] = SDL_CreateTextureFromSurface(renderer, surfaceTxt);
        SDL_QueryTexture( atlas->table[i], NULL, NULL,
                          &atlas->surfWidth,
                          &atlas->surfHeight);
        SDL_FreeSurface(surfaceTxt);
    }
    
    TTF_CloseFont(font);
    return atlas;
}

SDL_Texture *atlasGetGlyph(Atlas *atlas, char c) {
    nullDie(atlas);
    if (c < 0 || c >= ATLAS_SIZE) {
        die("atlasGetGlyph got out of range char");
    }
    return atlas->table[(int)c];
}

void freeAtlas(Atlas *atlas) {
    for (int i=0; i<ATLAS_SIZE; i++) {
        if (atlas->table[i]) {
            SDL_DestroyTexture(atlas->table[i]);
        }
    }
}

#endif // ATLAS

