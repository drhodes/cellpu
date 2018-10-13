// @file
// @brief This file is marvelous.

#ifndef CELL_H
#define CELL_H

#include <stdbool.h>

#include "atlas.h"
#include "common.h"
#include <SDL2/SDL.h>

// The unit cell


typedef struct {
    int x, y, value, size;
    bool selected, broadcasting, listening;
    int dataReg, colReg, rowReg;
    int op; // this will be of type Instruction soon.
} Cell;


Cell* newCell(int x, int y);

void cellSetColReg(Cell* cell, int n);
void cellSetRowReg(Cell* cell, int n);
void cellSetDataReg(Cell* cell, int n);

SDL_Color cellColor(Cell *cell);

void cellSelect(Cell *cell);
void cellDeselect(Cell *cell);

void cellSetBroadcast(Cell *cell, bool b);
void cellSetListen(Cell *cell, bool b);
void cellSetListen(Cell *cell, bool b);

SDL_Color cellBorderColor(Cell *cell);


void cellRender(Cell *cell, Atlas *atlas, SDL_Renderer *renderer);

// move these to display.c or something.
void borderBox(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color border, SDL_Color fill);
void drawText(SDL_Renderer *renderer, Atlas *atlas, int x, int y, const char* txt);

#endif // CELL_H
