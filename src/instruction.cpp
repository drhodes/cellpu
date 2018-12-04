#include <SDL2/SDL.h>

#include <string>

#include "err.hh"
#include "instruction.hh"
#include "common.hh"

Instruction::Instruction(string name, SDL_Color c) {
  m_name = name;
  m_color = c;
}

void
Instruction::apply(Grid &grid, Cell &cell) { }

// -------------------------------------------------------------------------------------------------
NOOP::NOOP() : Instruction("NOOP", {0x30, 0x30, 0x30, 0xFF}) {}

void 
NOOP::apply(Grid &grid, Cell &cell) {
}

// -------------------------------------------------------------------------------------------------
AND::AND() : Instruction("AND", {0xFF, 0x30, 0x30, 0xFF}) {}

void
AND::apply(Grid &grid, Cell &cell) {  
  Cell* argCell1 = grid.getNbr(cell.x_, cell.y_, cell.getArgWay1());
  Cell* argCell2 = grid.getNbr(cell.x_, cell.y_, cell.getArgWay2());
  byte arg1 = argCell1->dataReg_;
  byte arg2 = argCell2->dataReg_;    
  cell.dataReg_ = arg1 & arg2;
}




































// function NOP()
//    local f = function(x)
//       return x
//    end   
//    return Instruction("NOP", f, {0x30, 0x30, 0x30, 0xFF})
// end




// Instruction*
// instEmpty() {
//   Instruction *inst = (Instruction*)calloc(sizeof(Instruction), 1);
//   return inst;
// }

// void
// opNOP(struct Grid *grid, struct Cell* cell) {
//     // nop doesn't do anything.
// }

// Instruction*
// iNOP() {
//     Instruction *inst = instEmpty();
//     strcpy(inst->name, "NOP");
//     inst->color = (SDL_Color){0x30, 0x30, 0x30, 0xFF};
//     inst->op = opNOP;
//     return inst;
// }

// // function CMPLE()
// //    local f = function(x, y)
// //       if x <= y then return 1 else return 0 end
// //    end
// //    return Instruction("CMPLE", f, {0x30, 0xAA, 0x30, 0xFF})
// // end

// // Bitwise AND of two nbr cells. -------------------------------------------------------------------

// static void
// opAND(struct Grid *grid, struct Cell* cell) {
//     nullDie(grid); nullDie(cell);
//     Cell* argCell1 = grid->getNbr(cell->x_, cell->y_, cell->getArgWay1());
//     Cell* argCell2 = grid->getNbr(cell->x_, cell->y_, cell->getArgWay2());
//     byte arg1 = argCell1->dataReg_;
//     byte arg2 = argCell2->dataReg_;    
//     cell->dataReg_ = arg1 & arg2;
// }

// Instruction*
// iAND() {
//     Instruction *inst = instEmpty();
//     strcpy(inst->name, "AND");
//     inst->color = (SDL_Color){0xFF, 0x30, 0x30, 0xFF};
//     inst->op = opAND;
//     return inst;
// }




// // Bitwise AND of two nbr cells. -------------------------------------------------------------------

// static void
// opCMPLE(struct Grid* grid, struct Cell* cell) {
//     // make sure there are exactly two input direction flags set.
//     // cell->
// }

// Instruction*
// iCMPLE() {
//     Instruction *inst = instEmpty();
//     strcpy(inst->name, "CMPLE");
//     inst->color = (SDL_Color){0x30, 0xAA, 0x30, 0xFF};
//     inst->op = opCMPLE;
//     return inst;
// }

// void freeInstruction(Instruction* inst) {
//     free(inst);
// }

