// @file
// @brief This file is marvelous.
#pragma once

#include <SDL2/SDL.h>

#define ATLAS_SIZE 127

class Atlas {
 public:
    SDL_Texture* table_[ATLAS_SIZE];
    int surfWidth_, surfHeight_;
    
    Atlas(SDL_Renderer *renderer, const char *fontFilename, int size);    
    SDL_Texture *getGlyph(char);
  ~Atlas();
};




