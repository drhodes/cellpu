#pragma once

#include "cell.hh"
#include "display.hh"
#include "grid-edit.hh"
#include "grid.hh"
#include "visit.hh"

class RenderVisitor : public BaseVisitor {
 private:
 public:
  RenderVisitor() {
  }

  void
  visit(Grid &g) {
    // render grid cells.
    for (int row = 0; row < g.getSize(); row++) {
      for (int col = 0; col < g.getSize(); col++) {
        g.getCell(col, row)->render(g.getAtlas(), display::getRenderer());
      }
    }
  }
};
