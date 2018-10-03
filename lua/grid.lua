-- A grid object. this may have to be moved to C.  Potentially would
-- like to simulate very large system ~1M nodes.

function Grid(n)
   -- grid object contains many cells --------------------------------------------------------------
   local self = {
      size = n,
      cells = {}
   }

   for i=0, self.size do
      self.cells[i] = {}
      for j=0, self.size do
         self.cells[i][j] = Cell(i, j, {100,100,255,255})
      end
   end
   
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

   self.selectRowSegment = function(x, y, e, w)
      local left = x - w
      local right = x + e
      x = left
      
      while x <= right do
         self.cells[x][y].select()
         x = x + 1
      end
   end
   
   self.crossSelect = function(x, y, n, e, s, w)
      -- select a cross of cells, that is a row segment intersected
      -- with a column segment, relative to x, y
      self.selectColSegment(x, y, n, s)
      self.selectRowSegment(x, y, e, w)
   end

   self.alterSelected = function(f) 
      for i=0, self.size do
         for j=0, self.size do
            c = self.cells[i][j]
            if c.selected then
               f(c)
            end
         end
      end
   end
   
   return self -- end of class grid.
end

function gridtest()   
   local g = Grid(14)
   local c1 = g.cells[5][5]
   c1.op = CMP()
   c1.data = 7
   g.crossSelect(5,5, 4,3,3,4)
   c1.setBroadcast(true)
   c1.deselect()
   function setVal(cell)
      cell.data = 5
      cell.op = CMP()
   end
   
   g.alterSelected(setVal)      
   g.render()
   update()
end

print("loaded grid")
