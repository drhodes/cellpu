-- A grid object. this may have to be moved to C.  Potentially would
-- like to simulate very large system ~1M nodes.

function Grid(n)
   -- grid object contains many cells --------------------------------------------------------------
   self = {
      size = n,
      cells = {},
   }

   -- init cells
   function init()
      for i=0, self.size do
         self.cells[i] = {}
         for j=0, self.size do
            self.cells[i][j] = "cell"
            -- print(self.cells[i][j])
         end
      end
   end
   init()
         
   -------------------------------------------------------------------------------------------------
   self.show = function()
      return "<Grid size=" .. self.size .. ">"
   end

   
   return self
end


print("loaded grid")
