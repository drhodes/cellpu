// @file
// @brief something something doughnuts
#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "opcode.h"
#include "instruction.h"

struct Grid;

typedef enum PortCfgType { TWO_PORT_CFG, ONE_PORT_CFG } PortCfgType;

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
    int x, y, value, size;
    bool selected, broadcasting, listening;
    byte dataReg, colReg, rowReg;
    CellConfig cfg;
    struct Instruction *inst;

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



// move these to display.h or something.
void borderBox(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color border, SDL_Color fill);
void drawText(SDL_Renderer *renderer, Atlas *atlas, int x, int y, string);

