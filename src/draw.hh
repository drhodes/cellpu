#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// #include <assert.h>
// #include <stdbool.h> 
// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
#include <string>

#include "atlas.hh"

namespace draw {
  void borderBox(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color border, SDL_Color fill);
  void text(SDL_Renderer *renderer, Atlas &atlas, int x, int y, std::string txt);
}
