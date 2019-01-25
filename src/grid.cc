#include <array>
#include <functional>
#include <utility>

#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>

#include "err.hh"
#include "grid.hh"
#include "common.hh"
#include "cell.hh"
#include "bbox.hh"
#include "display.hh"
#include "instruction.hh"
#include "cmdr.hh"
#include "lua.hh"

using namespace std;
extern LuaMgr lman; // main.cc

Grid::Grid(int size) {
  if (size < 1) die("got bad size for new grid");
  m_size = size;
  
  for (int row=0; row < m_size; row++) { 
    vector<shared_ptr<Cell>> curRow;
    for (int col=0; col < m_size; col++) {
      auto c = make_shared<Cell>(row, col);
      curRow.push_back(c);
      if (row % 2 == 0) {
        c->setInstruction(make_shared<AND>());
      }
    }
    m_cells.push_back(curRow);
  }  
}

Grid::~Grid() {
  delete &m_atlas;
}

void
Grid::render() {
  // render grid cells.
  for (int row=0; row < m_size; row++) {
    for (int col=0; col < m_size; col++) {
      m_cells[row][col]->render(m_atlas, display::getRenderer());
    }
  }
}

void
Grid::bbox(BBox& bb) {
  int cellSize = getCell(0, 0)->size();
  bb.top = 0;
  bb.left = 0;
  bb.height = m_size * cellSize; 
  bb.width  = m_size * cellSize; 
}

int
Grid::width() {
  BBox bb;
  bbox(bb);
  return bb.width;
}


bool
Grid::containsPoint(Sint32 x, Sint32 y) {    
  BBox bb;
  bbox(bb);
  return bb.containsPx(x, y);
}

void
Grid::accept(std::shared_ptr<Visitor> v) {  
  v->visit(*this);  
}

void
Grid::selectCell(int col, int row) {
  auto c = getCell(col, row);
  c->selected(true);
}

shared_ptr<Cell>
Grid::cursorCell(Sint32 pixelX, Sint32 pixelY) {
  if (!containsPoint(pixelX, pixelY)) return {};
  int cellSize = getCell(0, 0)->size(); // get the size of an arbitary cell
  int col = pixelX / cellSize;
  int row = pixelY / cellSize;
  return getCell(col, row);
}

shared_ptr<Cell>
Grid::getCell(int col, int row) const {
  if (col < 0) terr("col must be greater than 0");
  if (row < 0) terr("row must be greater than 0");
  if (col >= m_size) terr("col cell coordinate outside of grid");
  if (row >= m_size) terr("row cell coordinate outside of grid");
  return m_cells[col][row];
}

void
Grid::setSelectAllCells(bool b) {
  for (int x = 0; x < m_size; x++) {
    for (int y = 0; y < m_size; y++) {
      getCell(x, y)->selected(b);
    }
  }
}

vector<shared_ptr<Cell>>
Grid::getAllSelectedCells() {
  auto cells = new vector<std::shared_ptr<Cell>>();
  for (int x = 0; x < m_size; x++) {
    for (int y = 0; y < m_size; y++) {
      auto c = getCell(x, y);
      if (c->selected()) {
        cells->push_back(c);
      }
    }
  }
  return *cells; // this is a move.
}

shared_ptr<Cell>
Grid::getNbr(int x, int y, Way w) {
  switch (w) {
  case N: return getCell(x, y-1);
  case S: return getCell(x, y+1);
  case E: return getCell(x+1, y);
  case W: return getCell(x-1, y);
  default: terr("recieved an impossible Way argument");
  } 
}

int
Grid::bottom() {
  BBox bb;
  bbox(bb);
  return bb.bottom();
}

void
Grid::zoom(int factor) {
  m_zoom = factor;
  zoomCells();
}

void
Grid::zoomCells() {
  // this is going to change eventually.
  // only zoom the displayed cells
  // TODO only render the cells in the viewport.
  for (int row=0; row < m_size; row++) { 
    for (int col=0; col < m_size; col++) {
      m_cells[row][col]->setZoom(m_zoom);
    }
  }
}
