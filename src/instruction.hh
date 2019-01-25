#pragma once

#include <SDL2/SDL.h>

#include "cell.hh"
#include "common.hh"
#include "grid.hh"

class Grid;
class Cell;

// -- Instructions.
// -----------------------------------------------------------------------------------
// -- GridInstruction
// -- CellInstruction

class Instruction {
 public:
  string m_name;
  SDL_Color m_color;

  Instruction(string, SDL_Color);
  ~Instruction();

  void apply(Grid &grid, Cell &cell);
};

// -------------------------------------------------------------------------------------------------

#define INSTRUCTION(INAME)              \
  class INAME : public Instruction {    \
   public:                              \
    INAME();                            \
    void apply(Grid &grid, Cell &cell); \
  };

INSTRUCTION(NOOP)
INSTRUCTION(AND)
