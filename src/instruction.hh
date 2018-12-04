#pragma once

#include <SDL2/SDL.h>

#include "common.hh"
#include "grid.hh"
#include "cell.hh"
#include "opcode.hh"


class Grid; // fwd decls
class Cell;

// -- Instructions. -----------------------------------------------------------------------------------

// -- GridInstruction
// -- CellInstruction

// function Instruction(name, oper, color)   
//    local self = {
//       name = name,
//       oper = oper,
//       color = color,
//    }

// struct Grid;
// struct Cell;

class Instruction {
public:
  string m_name;
  SDL_Color m_color;    

  Instruction(string, SDL_Color);
  virtual void apply(Grid &grid, Cell &cell);
};


class NOOP : public Instruction {
public:
  NOOP();
  void apply(Grid &grid, Cell &cell);
};



class AND : public Instruction {
public:
  AND();
  void apply(Grid &grid, Cell &cell);
};


/*
class CMPLE : public Instruction {};

class DATA : public Instruction {}; // cell instruction as data
class PROC : public Instruction {}; // cell instruction as instruction??


class AND : public Instruction {};
class OR : public Instruction {};
*/

// Instruction &iNOP();
// Instruction &iCMPLE();

// Instruction &iDATA(); // instruction as data.
// Instruction &iPROC(); // data as instruction.

// // bitwise AND of two cells.
// Instruction &iAND();
// Instruction &iOR();




//    self.render = function(x, y)
//       putText(self.name, x, y)
//    end

//    return self
// end

// -- Cell Instructions -------------------------------------------------------------------------------

// function NOP()
//    local f = function(x)
//       return x
//    end   
//    return Instruction("NOP", f, {0x30, 0x30, 0x30, 0xFF})
// end


    
// function CMPLE()
//    local f = function(x, y)
//       if x <= y then return 1 else return 0 end
//    end
//    return Instruction("CMPLE", f, {0x30, 0xAA, 0x30, 0xFF})
// end

// function CAST(n,s,e,w)
//    local f = function()
//       error ("Cast instruction undefined")
//    end
//    return Instruction("CAST",  f, {0xAA, 0x30, 0x30, 0xFF})
// end

// function ROWCHAN()
//    local f = function()
//       error ("ROWCHAN instruction undefined")
//    end
//    return Instruction("═ROWCHAN═", f, {0xAA, 0x30, 0xAA, 0xFF})
// end

// function ADDE()
//    local f = function()
//       error ("ROWCHAN instruction undefined")
//    end
//    return Instruction("", f, {0xAA, 0x30, 0x30, 0xFF})
// end

// function CMPSWP(d1, d2)
//    local f = function(grid, cell)
//       c1 = grid.getRelCell(cell, d1)
//       c2 = grid.getRelCell(cell, d2)
//       if c1.data < c2.data then
//          tmp = c2.data
//          c2.data = c1.data
//          c1.data = tmp
//       end
//    end
//    return Instruction("CMPSWP", f, {0xBB, 0x78, 0x23, 0xFF})
// end

// function DATA()
//    local f = function()
//       error ("DATA instruction undefined")
//    end
//    return Instruction("DATA", f, {0xBB, 0xBB, 0xBB, 0xFF})
// end


// print("loaded instruction")






