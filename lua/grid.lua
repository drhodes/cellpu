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
         self.cells[i][j] = Cell(i, j, {0,0,255,255})
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
         print(self.cells[x][y].color)
         x = x + 1
      end
   end
   
   self.broadcastSelect = function(x, y, n, e, s, w)
      -- select a cross of cells, that is a row segment intersected
      -- with a column segment, relative to x, y
      self.selectColSegment(x, y, n, s)
      self.selectRowSegment(x, y, e, w)
   end
   
   return self
end



function gridtest()   
   g = Grid(10)
   g.cells[5][5].op = CMP()
   g.broadcastSelect(5,5,2,2,2,2)
   g.render()
   update()
end

print("loaded grid")
