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

Grid::Grid(int size) :
  m_atlas(*new Atlas("./media/FIXED_V0.TTF", 8))
{
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
  int cellSize = getCell(0, 0)->size_;
  bb.top = 0;
  bb.left = 0;
  bb.height = cellSize * m_size; 
  bb.width  = cellSize * m_size; 
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

// void
// Grid::registerLuaCallbacks() {
//   auto L = lman.getLuaState();

//   lua_pushcfunction(L, foo);
//   // lua_setglobal(L, "selectCell");
// }

void
Grid::selectCell(int x, int y) {
  auto c = getCell(x, y);
  c->setSelect(true);
}

shared_ptr<Cell>
Grid::cursorCell(Sint32 pixelX, Sint32 pixelY) {
  if (!containsPoint(pixelX, pixelY)) return {};
  int cellSize = getCell(0, 0)->size_;
  int x = pixelX / cellSize;
  int y = pixelY / cellSize;    
  return getCell(x, y);
}

shared_ptr<Cell>
Grid::getCell(int x, int y) const {
  if (x < 0) terr("x must be greater than 0");
  if (y < 0) terr("y must be greater than 0");
  if (x >= m_size) terr("x cell coordinate outside of grid");
  if (y >= m_size) terr("y cell coordinate outside of grid");
  return m_cells[x][y];
}

void
Grid::setSelectAllCells(bool b) {
  for (int x = 0; x < m_size; x++) {
    for (int y = 0; y < m_size; y++) {
      getCell(x, y)->setSelect(b);
    }
  }
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
