#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <SDL2/SDL.h>

#include "common.h"
#include "grid.h"
#include "cell.h"
#include "opcode.h"

// -- Instructions. -----------------------------------------------------------------------------------

// -- GridInstruction
// -- CellInstruction

// function Instruction(name, oper, color)   
//    local self = {
//       name = name,
//       oper = oper,
//       color = color,
//    }


struct Grid;
struct Cell;

typedef struct Instruction {
    char name[8];
    SDL_Color color;    
    void (*op)(struct Grid*, struct Cell*);
} Instruction;




Instruction* iNOP();
Instruction* iCMPLE();

void freeInstruction(Instruction* inst);


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



#endif // INSTRUCTION_H
