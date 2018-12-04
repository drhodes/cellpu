#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <exception>
#include <map>

#include "atlas.hh"
#include "err.hh"

// TODO table should be a hash table to hand unicode
Atlas::Atlas(SDL_Renderer *renderer, const char *fontFilename, int size) {
  TTF_Font* font = TTF_OpenFont(fontFilename, size);
  nullDie(font);
  TTF_SetFontHinting(font, TTF_HINTING_NONE); //TTF_HINTING_LIGHT);
    
  SDL_Color white = {255, 255, 255, 255};

  for (char c = 0; c<ATLAS_SIZE; c++) {
    SDL_Surface* surfaceTxt = TTF_RenderGlyph_Blended(font, c, white);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surfaceTxt);
    SDL_QueryTexture( tex, NULL, NULL, &surfWidth_, &surfHeight_);
    m_table.insert(std::pair<char, SDL_Texture*>(c, tex));
    SDL_FreeSurface(surfaceTxt);
  }
  
  TTF_CloseFont(font);
}

SDL_Texture*
Atlas::getGlyph(char c) throw() {
  std::map<char, SDL_Texture*>::iterator tup = m_table.find(c);
  if (tup == std::end(m_table)) {
    throw runtime_error("atlasGetGlyph got unknown character: " + c);
  }
  return tup->second;
}

Atlas::~Atlas() {
  for (auto p : m_table) {
    SDL_DestroyTexture(p.second);
  }
}
