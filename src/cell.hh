// @file
// @brief something something doughnuts
#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include "opcode.hh"
#include "instruction.hh"
#include "state-machine.hh"

class Grid;
class Instruction;

enum class PortCfgType { ONE_PORT ,
                         TWO_PORT };

typedef struct TwoPortCfg {
  Dir leftInput, rightInput;
} TwoPortCfg;


typedef struct OnePortCfg {
  Dir input;
} OnePortCfg;


typedef struct PortCfg {
  PortCfgType type;    
  union {
    TwoPortCfg inputTwoPort;
    OnePortCfg inputOnePort;        
  } value;
} PortCfg;


typedef struct CellConfig {
  Opcode opcode; 
  Way heading; 
  bool broadcasting; // is the cell broadcasting?
  DirFlags broadcastFlags; // LRFB flags -> 1000, 0100, 0010, 0001.
  PortCfg inputPorts; // LRFB flags -> 1000, 0100, 0010, 0001.
  bool running; // is the cell running or not?
  // cell outputs
} CellConfig;

enum class CellState {
                      Resting,
                      Highlighted,
                      Blinking,
                      Processing,
                      Listening,
};

enum class CellTrans {
                      MouseOver,
                      MouseExit,
                      MouseClick,                      
};

class Cell {
public: 
  int x_, y_, value_, size_;
  bool selected_, broadcasting_, listening_;
  char dataReg_, colReg_, rowReg_;
  CellConfig cfg_;
  shared_ptr<Instruction> inst_; // this has to be a pointer because of an import cycle.
  
  Cell(int, int);
  Cell(const Cell&) = delete;
  ~Cell();

  void setColReg(int n);
  void setRowReg(int n);
  void setDataReg(int n);
  void setInstruction(shared_ptr<Instruction>);


  
  void setSelect(bool b);
  void setBroadcast(bool b);
  void setListen(bool b);

  SDL_Color color();

  void cycle(struct Grid *grid);
  void render(Atlas& atlas, SDL_Renderer *renderer);
  void cfgInputValidate();

  string instructionName();
    
  Way getArgWay1();
  Way getArgWay2();
};

