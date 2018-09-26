-- The unit cell


function Cell(n)   
   self = {
   }

   -- init cells
   function init()
   end
   init()
         
   -------------------------------------------------------------------------------------------------
   self.show = function()
      return "<Cell size=" .. self.size .. ">"
   end

   
   return self
end


print("loaded cell")
