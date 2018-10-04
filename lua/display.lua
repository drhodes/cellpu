
function setRed() setColor(255, 0, 0, 255) end
function setGreen() setColor(0, 255, 0, 255) end
function setBlue() setColor(0, 0, 255, 255) end
function setBlack() setColor(0, 0, 0, 255) end

function setRandomColor()
   r = math.random(255)
   g = math.random(255)
   b = math.random(255)
   a = math.random(255)
   setColor(r,g,b,a)
end

function boxes()
   for i=1,100 do
      setRandomColor()
      drawBox(i*2, i*2, i*2, i*5)
   end
   update()
end

function borderBox(x, y, h, w, bColor, color)
   setColor(bColor[1], bColor[2], bColor[3], bColor[4])
   drawBox(x,y,h,w)
   setColor(color[1], color[2], color[3], color[4])
   drawBox(x+1, y+1, h-2, w-2)
end

function tiles()
   local TILE_SIZE = 10
   local tilesWide = 60

   local x = 1
   while x < tilesWide do      
      local y = 1
      while y < tilesWide do
         setRandomColor()
         drawBox(x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE)
         y = y + 1
      end
      x = x + 1
   end
   update()
end

print("loaded display")
