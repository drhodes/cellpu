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


   self.selectColSegment = function()
   end

   self.selectRowSegment = function()
   end
   
   
   return self
end



function gridtest()
   g = Grid(10)
   g.render()
   update()
end

print("loaded grid")
