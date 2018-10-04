-- The unit cell

function Cell(x, y, c)   
   local self = {
      x = x,
      y = y,
      value = 0,
      size = 60,
      selected = false,
      broadcasting = false,
      listening = false,      
      data = 0,
      colReg = 0, -- photonics column register
      rowReg = 0, -- photonics row register
      op = NOP(),
   }         

   self.setColReg = function(n) self.colReg = n end
   self.setRowReg = function(n) self.rowReg = n end
   self.color = function() return self.op.color end
   
   
   self.show = function()
      return "<Cell size=" .. self.size .. ">"
   end

   self.select = function()
      self.selected = true
   end

   self.deselect = function()
      self.selected = false
   end

   self.setBroadcast = function(bool)
      self.broadcasting = bool
      self.listening = not bool
   end

   self.setListen = function(bool)
      self.listening = bool
      self.broadcasting = not bool
   end
   
   self.setCap = function(dir)      
   end

   self.borderColor = function()
      if self.selected then
         return {0x30, 0x40, 0xFF, 0xFF}
      else 
         return {0x00, 0x00, 0x00, 0xFF}
      end
   end
   
   
   self.render = function()
      borderBox(self.x * self.size,
                self.y * self.size,
                self.size, self.size, self.borderColor(), self.color())
      
      drawText(self.x * self.size + 4,
               self.y * self.size + 4,
               "[" .. tostring(self.x) .. " " .. tostring(self.y) .. "]")
      
      drawText(self.x * self.size + 4,
               self.y * self.size + 16,
               self.op.name)
      
      drawText(self.x * self.size + self.size / 2,
               self.y * self.size + self.size / 2,
               tostring(self.data))
      
      drawText(self.x * self.size + self.size / 2 + self.size/4,
               self.y * self.size + self.size / 2,
               tostring(self.rowReg))
      
      drawText(self.x * self.size + self.size / 2,
               self.y * self.size + self.size / 2 + self.size/4,
               tostring(self.colReg))
   end

   return self -- 
end

print("loaded cell")

