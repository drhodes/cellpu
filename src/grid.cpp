#include "err.h"
#include "grid.h"
#include "common.h"
#include "cell.h"
#include "bbox.h"

Grid*
newGrid(int size, int displaySize, Atlas *atlas) {
    if (size < 1) die("got bad size for new grid");
    Grid *grid = (Grid*)calloc(sizeof(Grid), 1);
    
    grid->atlas = atlas;
    grid->size = size;
    grid->displaySize = displaySize;
    grid->cells = (Cell***)calloc(sizeof(Cell***), size);
    //grid->editor = newGridEditor();
    
    for (int row=0; row<size; row++) {
        grid->cells[row] = (Cell**)calloc(sizeof(Cell**), size);
        for (int col=0; col<size; col++) {
            grid->cells[row][col] = new Cell(row, col);
        }
    }
    return grid;
}

void
gridRender(Grid *grid, SDL_Renderer *renderer) {
    // render grid cells.
    for (int row=0; row < grid->displaySize; row++) {
        for (int col=0; col < grid->displaySize; col++) {
            grid->cells[row][col]->render(grid->atlas, renderer);
        }
    }
}

void
gridBBox(Grid *grid, BBox *bb) {
    nullDie(grid);
    nullDie(bb);
    int cellSize = grid->cells[0][0]->size_;

    bb->top = 0;
    bb->left = 0;
    bb->height = cellSize * grid->displaySize;
    bb->width  = cellSize * grid->displaySize;    
}

bool
gridContainsPoint(Grid *grid, Sint32 x, Sint32 y) {    
    nullDie(grid);
    BBox bb;
    gridBBox(grid, &bb);
    return bb.containsPx(x, y);
}

Cell*
gridCursorCell(Grid *grid, Sint32 pixelX, Sint32 pixelY) {
    nullDie(grid);
    if (!gridContainsPoint(grid, pixelX, pixelY)) return NULL;
    
    int cellSize = grid->cells[0][0]->size_;
    int x = pixelX / cellSize;
    int y = pixelY / cellSize;    
    return grid->cells[x][y];
}

Cell*
gridGetCell(Grid *grid, int x, int y) {
    nullDie(grid);
    if (x < 0) {
        perr("x must be greater than 0");
        return NULL;
    }
    if (y < 0) {
        perr("y must be greater than 0");
        return NULL;
    }
    if (x >= grid->size) {
        perr("x cell coordinate outside of grid");
        return NULL;
    }
    if (y >= grid->size) {
        perr("y cell coordinate outside of grid");
        return NULL;
    }
    return grid->cells[x][y];
}


void
gridCycleCell(Grid *grid, int x, int y) {
    Cell* c = gridGetCell(grid, x, y);
    c->cycle(grid);
}

void gridSetSelectAllCells(Grid *grid, bool b) {
    nullDie(grid)
    for (int x = 0; x < grid->size; x++) {
        for (int y = 0; y < grid->size; y++) {
            Cell *c = gridGetCell(grid, x, y);
            nullDie(c);
            c->setSelect(b);
        }
    }
}

bool
gridProcessEvent(Grid *grid, SDL_Event *ev) {
    nullDie(grid); nullDie(ev);
    
    // hack together some spaghetti state handling and then build a
    // state machine. Either the grid has focus or it doesn't.
    
    switch (ev->type) {
    case SDL_KEYDOWN: {
        printf("GOT MOUSEDOWN IN gridProcessEvent\n");
        break;
    }
        
    case SDL_MOUSEMOTION: {
        Sint32 x = ev->motion.x;
        Sint32 y = ev->motion.y;
        Cell *c = gridCursorCell(grid, x, y);
        if (!c) break;
        
        printf("OVER CELL: %d, %d\n", c->x_, c->y_);        
    }}
    
    return true;
}

struct Cell*
gridGetNbr(Grid *grid, int x, int y, Way w) {
    switch (w) {
    case N: return gridGetCell(grid, x, y-1);
    case S: return gridGetCell(grid, x, y+1);
    case E: return gridGetCell(grid, x+1, y);
    case W: return gridGetCell(grid, x-1, y);
    }
    die("bad code path");
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
