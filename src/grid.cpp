#include <array>

#include "err.hh"
#include "grid.hh"
#include "common.hh"
#include "cell.hh"
#include "bbox.hh"
#include "display.hh"

using namespace std;

Grid::Grid(int size, int displaySize, shared_ptr<Atlas> atlas) {
  if (size < 1) die("got bad size for new grid");
  m_atlas = atlas;
  m_size = size;
  m_displaySize = displaySize;
  
  for (int row=0; row<size; row++) { 
    vector<shared_ptr<Cell>> curRow;
    for (int col=0; col<size; col++) {
      auto c = make_shared<Cell>(row, col);
      curRow.push_back(c);
    }
    m_cells.push_back(curRow);
  }
}

void
Grid::render() {
  // render grid cells.
  for (int row=0; row < m_displaySize; row++) {
    for (int col=0; col < m_displaySize; col++) {
      m_cells[row][col]->render(m_atlas, display::getRenderer());
    }
  }
}

void
Grid::bbox(BBox& bb) {
  int cellSize = m_cells[0][0]->size_;
  
  bb.top = 0;
  bb.left = 0;
  bb.height = cellSize * m_displaySize;
  bb.width  = cellSize * m_displaySize;    
}

bool
Grid::containsPoint(Sint32 x, Sint32 y) {    
  BBox bb;
  bbox(bb);
  return bb.containsPx(x, y);
}

shared_ptr<Cell>
Grid::cursorCell(Sint32 pixelX, Sint32 pixelY) {
  if (!containsPoint(pixelX, pixelY)) return nullptr;
  //cerr << "cursorCell: x=" << pixelX << ", y=" << pixelY << endl;
  int cellSize = m_cells[0][0]->size_;
  int x = pixelX / cellSize;
  int y = pixelY / cellSize;    
  return m_cells[x][y];
}

shared_ptr<Cell>
Grid::getCell(int x, int y) const {
  if (x < 0) terr("x must be greater than 0");
  if (y < 0) terr("y must be greater than 0");
  if (x >= m_size) terr("x cell coordinate outside of grid");
  if (y >= m_size) terr("y cell coordinate outside of grid");
  return m_cells[x][y];
}

// void
// gridCycleCell(const Grid &grid, int x, int y) {
//     Cell* c = gridGetCell(grid, x, y);
//     c->cycle(grid);
// }

void
Grid::setSelectAllCells(bool b) {
  for (int x = 0; x < m_size; x++) {
    for (int y = 0; y < m_size; y++) {
      getCell(x, y)->setSelect(b);
    }
  }
}

bool
Grid::processEvent(SDL_Event &ev) {
  // hack together some spaghetti state handling and then build a
  // state machine. Either the grid has focus or it doesn't.
  
  switch (ev.type) {
  case SDL_KEYDOWN: {
    printf("GOT MOUSEDOWN IN gridProcessEvent\n");
    break;
  }
    
  case SDL_MOUSEMOTION: {
    Sint32 x = ev.motion.x;
    Sint32 y = ev.motion.y;
    if (containsPoint(x, y)) {
      auto c = cursorCell(x, y);
      if (!c) die("cell not found in grid, that's impossible");
    }
  }}
  return true;
}

shared_ptr<Cell>
Grid::getNbr(int x, int y, Way w) {
  try {
    switch (w) {
    case N: return getCell(x, y-1);
    case S: return getCell(x, y+1);
    case E: return getCell(x+1, y);
    case W: return getCell(x-1, y);
    default: terr("recieved an impossible Way argument");
    }
  } catch(exception e) {
    eerr(e, "bad code path");
  }
}





// void
// gridUpdateHoodView(Grid *grid, int x, int y) {
// }

/*
   
   -------------------------------------------------------------------------------------------------
   self.show = function()
      return "<Grid size=" .. self.size .. ">"
   end
   
   self.render = function()
      for i=0, self.size do
         for j=0, self.size do
            self.cells[i][j].render()
         end
      end
   end

   self.selectColSegment = function(x, y, n, s)
      local top = y - n
      local bottom = y + s
      y = top
      
      while y <= bottom do
         self.cells[x][y].select()
         print(self.cells[x][y].color)
         y = y + 1
      end
   end

   self.selectColSegmentAbs = function(x, n, s)
      local cs = {};
      while n <= s do
         local c = self.cells[x][n]
         c.select()
         table.insert(cs, c)
         n = n + 1
      end
      return cs
   end
   
   self.selectRowSegmentAbs = function(y, w, e)
      local cs = {};
      while w <= e do
         self.assertRange(Loc(w, y))
         local c = self.cells[w][y]
         c.select()
         table.insert(cs, c)
         w = w + 1
      end
      return cs
   end

   self.assertRange = function(loc) 
      if loc.x < 0 or loc.x >= self.size or loc.y < 0 or loc.y >= self.size
      then error("location out of range: " .. tostring(loc.x) .. ", " .. tostring(loc.y))
      end
   end
   
   self.getCell = function(loc)
      self.assertRange(loc)
      return self.cells[loc.x][loc.y]
   end
   
   self.crossBroadcast = function(loc, dirVec)      
      local cellsN = self.selectColSegmentAbs(loc.x, loc.y - dirVec.n, loc.y-1)
      local cellsE = self.selectRowSegmentAbs(loc.y, loc.x+1, loc.x + dirVec.e)
      local cellsS = self.selectColSegmentAbs(loc.x, loc.y+1, loc.y + dirVec.s)
      local cellsW = self.selectRowSegmentAbs(loc.y, loc.x - dirVec.w, loc.x-1)

      broadcastCell = self.getCell(loc)
      for _, c in ipairs(cellsN) do c.setColReg(broadcastCell.data) end
      for _, c in ipairs(cellsE) do c.setRowReg(broadcastCell.data) end 
      for _, c in ipairs(cellsS) do c.setColReg(broadcastCell.data) end
      for _, c in ipairs(cellsW) do c.setRowReg(broadcastCell.data) end
   end
   
   self.getRelCell = function(cell, dir)
      if     dir == N then return self.getCell(Loc(cell.x, cell.y-1))
      elseif dir == E then return self.getCell(Loc(cell.x+1, cell.y))
      elseif dir == S then return self.getCell(Loc(cell.x, cell.y+1))
      elseif dir == W then return self.getCell(Loc(cell.x-1, cell.y))
      end
   end
   
   return self -- end of class grid.
end

*/
