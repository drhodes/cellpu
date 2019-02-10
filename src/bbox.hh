// @file
// @brief This file is marvelous.

#pragma once

#include <stdbool.h>

class BBox {
 public:
  int m_top, m_left, m_height, m_width;

  BBox();
  BBox(int, int, int, int);

  bool containsPx(int x, int y);
  void updateSize(int w, int h);

  void left(int x);
  void top(int x);
  void width(int x);
  void height(int x);

  int left();
  int top();
  int width();
  int height();

  int bottom();
  int right();
};
