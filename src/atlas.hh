// @file
// @brief This file is marvelous.
#pragma once

#include <SDL2/SDL.h>
#include <map>

#define ATLAS_SIZE 127

class Atlas {
public:
  int surfWidth_, surfHeight_;
  std::map<char, SDL_Texture*> m_table;

  
  Atlas(SDL_Renderer *renderer, const char *fontFilename, int size);    
  SDL_Texture *getGlyph(char) throw() ;
  ~Atlas();
};




