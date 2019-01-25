#pragma once

#include <memory>
#include <optional>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "atlas.hh"

namespace draw {
void borderBox(int x, int y, int w, int h, SDL_Color border, SDL_Color fill);
void text(Atlas& atlas, int x, int y, std::string txt);
}  // namespace draw
