-- A grid object. this may have to be moved to C.  Potentially would
-- like to simulate very large system ~1M nodes.

function DirVec(n, e, s, w)
   local v = {n=n, e=e, s=s, w=w}
   return v
end

function Loc(x, y)
   local loc = {x=x, y=y}
   return loc
end

function Grid(n)
   -- grid object contains many cells --------------------------------------------------------------
   local self = {
      size = n,
      cells = {}
   }

   for i=0, self.size do
      self.cells[i] = {}
      for j=0, self.size do
         self.cells[i][j] = Cell(i, j, {100,100,255,255})
      end
   end
   
   -------------------------------------------------------------------------------------------------
   self.show = function()
      return "<Grid size=" .. self.size .. ">"
   end
   
   self.render = function()
      for i=0, self.size do
         for j=0, self.size do
            self.cells[i][j].render()
         end
      end
   end

   self.selectColSegment = function(x, y, n, s)
      local top = y - n
      local bottom = y + s
      y = top
      
      while y <= bottom do
         self.cells[x][y].select()
         print(self.cells[x][y].color)
         y = y + 1
      end
   end

   self.selectColSegmentAbs = function(x, n, s)
      local cs = {};
      while n <= s do
         local c = self.cells[x][n]
         c.select()
         table.insert(cs, c)
         n = n + 1
      end
      return cs
   end
   
   self.selectRowSegmentAbs = function(y, w, e)
      local cs = {};
      while w <= e do
         self.assertRange(Loc(w, y))
         local c = self.cells[w][y]
         c.select()
         table.insert(cs, c)
         w = w + 1
      end
      return cs
   end

   self.assertRange = function(loc) 
      if loc.x < 0 or loc.x >= self.size or loc.y < 0 or loc.y >= self.size
      then error("location out of range: " .. tostring(loc.x) .. ", " .. tostring(loc.y))
      end
   end
   
   self.getCell = function(loc)
      self.assertRange(loc)
      return self.cells[loc.x][loc.y]
   end
   
   
   self.crossBroadcast = function(loc, dirVec)      
      local cellsN = self.selectColSegmentAbs(loc.x, loc.y - dirVec.n, loc.y-1)
      local cellsE = self.selectRowSegmentAbs(loc.y, loc.x+1, loc.x + dirVec.e)
      local cellsS = self.selectColSegmentAbs(loc.x, loc.y+1, loc.y + dirVec.s)
      local cellsW = self.selectRowSegmentAbs(loc.y, loc.x - dirVec.w, loc.x-1)

      broadcastCell = self.getCell(loc)
      for _, c in ipairs(cellsN) do c.setColReg(broadcastCell.data) end
      for _, c in ipairs(cellsE) do c.setRowReg(broadcastCell.data) end 
      for _, c in ipairs(cellsS) do c.setColReg(broadcastCell.data) end
      for _, c in ipairs(cellsW) do c.setRowReg(broadcastCell.data) end
   end
   
   
   return self -- end of class grid.
end

function gridtest()   
   local g = Grid(14)
   local c1 = g.getCell(Loc(5,5))
   c1.op = CAST(4,3,3,4)
   c1.data = 3
   g.crossBroadcast(Loc(5,5), DirVec(4,3,3,4))

   local c2 = g.getCell(Loc(2,2))
   c2.op = CAST(1,6,6,1)
   c2.data = 7
   g.crossBroadcast(Loc(2,2), DirVec(1,6,6,1))

   local c3 = g.getCell(Loc(5, 2))
   c3.op = CMPLE()   
   c3.data = c3.op.oper(c3.rowReg, c3.colReg)

   local c4 = g.getCell(Loc(2, 5))
   c4.op = CMPLE()   
   c4.data = c4.op.oper(c4.rowReg, c4.colReg)
   
   g.render()
   update()
end


function sortCfg()
   local g = Grid(10)
   local SIZE = 8
   local LEFT = 1
   local RIGHT = SIZE
   local TOP = 1
   local BOTTOM = SIZE
   
   for x = 1,8 do
      for y = 1,8 do
         if x ~= y then
            c = g.getCell(Loc(x,y))
            c.op = CMPLE()
         end         
      end
   end
   
   for x = LEFT,RIGHT do
      y=x
      c = g.getCell(Loc(x,x))
      c.op = CAST(0,0,0,0)
      c.data = math.random(1,9)
      
      n = y - TOP
      e = RIGHT - x
      s = BOTTOM - y
      w = x - LEFT
      g.crossBroadcast(Loc(x,y), DirVec(n, e, s, w))
   end

   for x = 1,8 do
      for y = 1,8 do
         if x ~= y then
            c = g.getCell(Loc(x,y))
            c.data = c.op.oper(c.rowReg, c.colReg)
         end         
      end
   end
   
   g.render()
   update()
end





print("loaded grid")
