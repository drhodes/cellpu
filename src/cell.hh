// @file
// @brief something something doughnuts
#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include "opcode.hh"
#include "instruction.hh"
#include "state-machine.hh"
#include "visit.hh"

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

class Cell :
  public Visitable
{
private:
  const int m_size = 30;
  char m_dataReg, m_colReg, m_rowReg;
  int m_col, m_row, m_value;
  int m_zoom;
  bool m_selected, m_broadcasting, m_listening;
  CellConfig m_cfg;
public: 
  shared_ptr<Instruction> m_inst; // this has to be a pointer because of an import cycle.
  
  Cell(int, int);
  Cell(const Cell&) = delete;
  ~Cell();

  void accept(shared_ptr<Visitor>);
  
  void setColReg(int n);
  void setRowReg(int n);
  void dataReg(int n);
  int dataReg();
  void setInstruction(shared_ptr<Instruction>);
  void setZoom(int zoom);

  void selected(bool b);
  bool selected();
  
  void setBroadcast(bool b);
  void setListen(bool b);


  
  
  int row();
  int col();

  
  string instructionName() const;
  int size() const;
  SDL_Color color() const;

  void cycle(struct Grid *grid);
  void render(Atlas& atlas, SDL_Renderer *renderer) const;
  void cfgInputValidate();

  string instructionName();
    
  Way getArgWay1();
  Way getArgWay2();
};

