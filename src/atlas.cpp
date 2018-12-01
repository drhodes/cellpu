#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <exception>

#include "atlas.h"
#include "err.h"

// TODO table should be a hash table to hand unicode
Atlas::Atlas(SDL_Renderer *renderer, const char *fontFilename, int size) {
  TTF_Font* font = TTF_OpenFont(fontFilename, size);
  nullDie(font);
  TTF_SetFontHinting(font, TTF_HINTING_NONE); //TTF_HINTING_LIGHT);
    
  SDL_Color white = {255, 255, 255, 255};
    
  for (int i=0; i<ATLAS_SIZE; i++) {
    SDL_Surface* surfaceTxt = TTF_RenderGlyph_Blended(font, i, white);
    table_[i] = SDL_CreateTextureFromSurface(renderer, surfaceTxt);
    SDL_QueryTexture( table_[i], NULL, NULL,
                      &surfWidth_,
                      &surfHeight_);
    SDL_FreeSurface(surfaceTxt);
  }
  
  TTF_CloseFont(font);
}
    //sprintf(msg, "atlasGetGlyph got out of range char: %c, %d", c, c);    
    //die(msg);
    //sprintf(msg, "atlasGetGlyph got out of range char: %c, %d", c, c);    
    //die(msg);

SDL_Texture*
Atlas::getGlyph(char c) throw() {
  if (c < 0 || c >= ATLAS_SIZE) {
    throw runtime_error("atlasGetGlyph got out of range char: " + c);
  }
  return table_[(int)c];
}

Atlas::~Atlas() {
    for (int i=0; i<ATLAS_SIZE; i++) {
        if (table_[i]) {
            SDL_DestroyTexture(table_[i]);
        }
    }
}
