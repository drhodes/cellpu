-- Instructions. -----------------------------------------------------------------------------------

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


function NOP()
   local f = function(x)
      return x
   end
   
   return Instruction("NOP", f)
end

-- What kind of instructions are there? for each permutation of
-- row broadcast, column broadcast, cell register.
-- nbr communication.


function CMP()
   local f = function(x, y)
      return x <= y
   end
   return Instruction("CMP", f)
end

   
