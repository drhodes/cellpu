// @file
// @brief something something doughnuts
#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "opcode.h"
#include "instruction.h"

struct Grid;

enum class PortCfgType { ONE_PORT,
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

class Cell {
 public: 
    int x_, y_, value_, size_;
    bool selected_, broadcasting_, listening_;
    byte dataReg_, colReg_, rowReg_;
    CellConfig cfg_;
    struct Instruction *inst_;

    Cell(int, int);

    void setColReg(int n);
    void setRowReg(int n);
    void setDataReg(int n);

    void setSelect(bool b);
    void setBroadcast(bool b);
    void setListen(bool b);

    SDL_Color color();

    void cycle(struct Grid *grid);
    void render(Atlas *atlas, SDL_Renderer *renderer);
    void cfgInputValidate();

    string instructionName();
    
    Way getArgWay1();
    Way getArgWay2();
};

