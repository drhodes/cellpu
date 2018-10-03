-- Instructions. -----------------------------------------------------------------------------------

-- GridInstruction
-- CellInstruction

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

-- Cell Instructions -------------------------------------------------------------------------------

function NOP()
   local f = function(x)
      return x
   end   
   return Instruction("NOP", f)
end

function CMP()
   local f = function(x, y)
      return x <= y
   end
   return Instruction("CMP", f)
end




print("loaded instruction")
