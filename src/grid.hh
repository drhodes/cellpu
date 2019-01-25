// @file
// @brief This file is marvelous.
#pragma once

#include <memory>
#include <vector>

#include "atlas.hh"
#include "bbox.hh"
#include "cell.hh"
#include "cmdr.hh"
#include "common.hh"
#include "visit.hh"

class Cell;

class Grid : public Visitable {
 private:
  std::vector<std::vector<shared_ptr<Cell>>> m_cells;
  Atlas m_atlas = Atlas("./media/FIXED_V0.TTF", 8);
  int m_zoom = 1;

 public:
  int m_size;

  Grid(int size);
  Grid(const Grid&) = delete;
  ~Grid() = default;

  void render();
  bool processEvent(SDL_Event&);
  void cycleCell(int x, int y);
  bool containsPoint(Sint32 x, Sint32 y);
  void setSelectAllCells(bool b);
  void bbox(BBox&);
  int bottom();
  int width();
  void resizeGrid(int n);
  void executeCmd(Cmd cmd);
  void selectCell(int x, int y);
  void registerLuaCallbacks();
  void accept(shared_ptr<Visitor>);
  void zoom(int factor);
  void zoomIn();
  void zoomOut();
  void zoomCells();
  vector<shared_ptr<Cell>> getAllSelectedCells();

  shared_ptr<Cell> getCell(int x, int y) const;
  shared_ptr<Cell> cursorCell(int pixelX, int pixelY);
  shared_ptr<Cell> getNbr(int x, int y, Way w);
};

class GridCmd : public Cmd {};

class GridCmdSelectCell : public GridCmd {
  int m_x, m_y;

 public:
  GridCmdSelectCell() = delete;
  GridCmdSelectCell(int x, int y) {
    m_x = x;
    m_y = y;
  }
};
