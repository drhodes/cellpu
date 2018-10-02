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
      
   }         

   self.show = function()
      return "<Cell size=" .. self.size .. ">"
   end

   self.select = function()
      self.selected = true
   end

   self.setBroadcast = function(bool)
      self.broadcasting = bool
      self.setListening(not bool)
   end

   self.setListen = function(bool)
      self.listening = bool
      self.setBroadcast(not bool)
   end

   self.setCap = function(dir)
   end
   
   
   
   self.render = function()
      blackBorderBox(self.x * self.size,
                     self.y * self.size,
                     self.size,
                     self.size,
                     self.color)
   end
   
   


   return self
end

print("loaded cell")

