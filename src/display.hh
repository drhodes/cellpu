#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace display {
SDL_Window *getWindow();
SDL_Renderer *getRenderer();
}  // namespace display

class Display {
 public:
  Display();
  ~Display();
};
