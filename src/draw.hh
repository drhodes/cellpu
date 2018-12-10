#pragma once

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "atlas.hh"

namespace draw {
  void borderBox(int x, int y, int w, int h, SDL_Color border, SDL_Color fill);
  void text(std::shared_ptr<Atlas> atlas, int x, int y, std::string txt);
}
