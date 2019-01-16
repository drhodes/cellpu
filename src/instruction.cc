#include <SDL2/SDL.h>

#include <string>
#include <optional>

#include "err.hh"
#include "instruction.hh"
#include "common.hh"

Instruction::Instruction(string name, SDL_Color c) {
  m_name = name;
  m_color = c;
}

Instruction::~Instruction() {
  cerr << "destroying instruction: " << m_name << endl;
}

void
Instruction::apply(Grid &grid, Cell &cell) { }

// -------------------------------------------------------------------------------------------------
NOOP::NOOP() : Instruction("NOOP", {0x9d, 0x02, 0x33, 0xFF}) {
  
}

void 
NOOP::apply(Grid &grid, Cell &cell) { }

// -------------------------------------------------------------------------------------------------
AND::AND() : Instruction("AND", {0xFF, 0x30, 0x30, 0xFF}) {}

void
AND::apply(Grid &grid, Cell &cell) {
  auto argCell1 = grid.getNbr(cell.x_, cell.y_, cell.getArgWay1());
  auto argCell2 = grid.getNbr(cell.x_, cell.y_, cell.getArgWay2());
  char arg1 = argCell1->dataReg_;
  char arg2 = argCell2->dataReg_;    
  cell.dataReg_ = arg1 & arg2;
}
