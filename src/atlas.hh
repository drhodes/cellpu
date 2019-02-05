// @file
// @brief This file is marvelous.
#pragma once

#include <SDL2/SDL.h>
#include <experimental/optional>
#include <map>

using namespace std;
using namespace std::experimental;
#define ATLAS_SIZE 127

class Atlas {
 public:
  int surfWidth_;
  int surfHeight_;
  std::map<char, SDL_Texture *> m_table;

  Atlas(const char *fontFilename, int size);
  Atlas(const Atlas &) = delete;

  optional<SDL_Texture *> getGlyph(char);
  ~Atlas();
};
