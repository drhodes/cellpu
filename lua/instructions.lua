-- Instructions. -----------------------------------------------------------------------------------

-- GridInstruction
-- CellInstruction

function Instruction(name, oper, color)   
   local self = {
      name = name,
      oper = oper,
      color = color,
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
   return Instruction("NOP", f, {0x30, 0x30, 0x30, 0xFF})
end

function CMPLE()
   local f = function(x, y)
      if x <= y then return 1 else return 0 end
   end
   return Instruction("CMPLE", f, {0x30, 0xAA, 0x30, 0xFF})
end

function CAST(n,s,e,w)
   local f = function()
      error ("Cast instruction undefined")
   end
   return Instruction("CAST",  f, {0xAA, 0x30, 0x30, 0xFF})
end



print("loaded instruction")
