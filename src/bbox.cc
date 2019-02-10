// @file
// @brief This file is marvelous.

#include "bbox.hh"

BBox::BBox() : m_top(0), m_left(0), m_height(0), m_width(0) {}

BBox::BBox(int m_top, int m_left, int m_height, int m_width)
    : m_top(m_top), m_left(m_left), m_height(m_height), m_width(m_width) {}

bool
BBox::containsPx(int x, int y) {
  return (m_left < x && x < m_left + m_width && m_top < y &&
          y < m_top + m_height);
}

int
BBox::bottom() {
  return m_top + m_height;
}

int
BBox::right() {
  return m_left + m_width;
}

// -------------------------------------------------------------------------------------------------

void
BBox::top(int x) {
  m_top = x;
}

void
BBox::left(int x) {
  m_left = x;
}

void
BBox::width(int x) {
  m_width = x;
}

void
BBox::height(int x) {
  m_height = x;
}

// -------------------------------------------------------------------------------------------------

int
BBox::top() {
  return m_top;
}

int
BBox::left() {
  return m_left;
}

int
BBox::height() {
  return m_height;
}

int
BBox::width() {
  return m_width;
}

void
BBox::updateSize(int w, int h) {
  width(w);
  height(h);
}
