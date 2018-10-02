-- The unit cell

function Cell(x, y, c)   
   local self = {
      x = x,
      y = y,
      value = 0,
      size = 80,
      color = c,
      selected = false,
      broadcasting = false,
      listening = false,
      data = 0,
      op = NOP(),
   }         

   self.show = function()
      return "<Cell size=" .. self.size .. ">"
   end

   self.select = function()
      self.selected = true
      self.color = {255,0,0,255}
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
   
   self.render = function()
      blackBorderBox(self.x * self.size,
                     self.y * self.size,
                     self.size, self.size, self.color)
      
      drawText(self.x * self.size + 4,
               self.y * self.size + 4,
               "[" .. tostring(self.x) .. " " .. tostring(self.y) .. "]")
      
      drawText(self.x * self.size + 4,
               self.y * self.size + 16,
               self.op.name)
      
      drawText(self.x * self.size + self.size / 2,
               self.y * self.size + self.size / 2,
               tostring(self.data))
   end

   return self
end

print("loaded cell")

