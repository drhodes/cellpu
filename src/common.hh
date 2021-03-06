// @file
// @brief types used everywhere.

#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef uint8_t byte;

typedef enum { N = 1, E = 2, S = 4, W = 8 } Way;

typedef int DirFlags;

typedef struct {
  int x, y;
} Loc;

typedef enum {
  L = 1,  // left
  R = 2,  // right
  F = 4,  // forward
  B = 8,  // backward
} Dir;

char headingToChar(Way w);
Way wayFromHeading(Way heading, Dir dir);

bool oddSecond();
bool oddMoment();
