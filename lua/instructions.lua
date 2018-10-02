-- The unit cell

function Instruction(name, oper)   
   local self = {
      name = name,
      oper = oper,
   }
   
   self.render = function(x, y)
      putText(self.name, x, y)
   end
   
   


   return self
end

print("loaded cell")

