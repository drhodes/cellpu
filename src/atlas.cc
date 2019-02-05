#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <exception>
#include <experimental/optional>
#include <map>

#include "atlas.hh"
#include "display.hh"
#include "err.hh"

using namespace std;

Atlas::Atlas(const char* fontFilename, int size) {
  TTF_Font* font = TTF_OpenFont(fontFilename, size);
  nullDie(font);
  TTF_SetFontHinting(font, TTF_HINTING_NONE);

  SDL_Color white = {255, 255, 255, 255};

  for (char c = 0; c < ATLAS_SIZE; c++) {
    SDL_Surface* surfaceTxt = TTF_RenderGlyph_Blended(font, c, white);
    SDL_Texture* tex =
        SDL_CreateTextureFromSurface(display::getRenderer(), surfaceTxt);
    SDL_QueryTexture(tex, NULL, NULL, &surfWidth_, &surfHeight_);
    m_table.insert(std::pair<char, SDL_Texture*>(c, tex));
    SDL_FreeSurface(surfaceTxt);
  }
  TTF_CloseFont(font);
}

optional<SDL_Texture*>
Atlas::getGlyph(char c) {
  std::map<char, SDL_Texture*>::iterator tup = m_table.find(c);
  if (tup == std::end(m_table)) {
    return nullopt;
  }
  return make_optional(tup->second);
}

Atlas::~Atlas() {
  cerr << "Atlas destroyed" << endl;
  for (auto p : m_table) {
    SDL_DestroyTexture(p.second);
  }
}
