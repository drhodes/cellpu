// @file
// @brief This file is marvelous.

#pragma once

#include <stdbool.h> 

class BBox {
 public:
  int top, left, height, width;

  BBox();
  BBox(int, int, int, int);
  
  bool containsPx(int, int);
  int bottom();
  
};
