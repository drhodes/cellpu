#pragma once

#include "grid.h"
#include "cell.h"

typedef struct GridEditor {
    Grid *grid;
    Cell *overCell;
    Cell *selectedCell;
    bool hasFocus;
} GridEditor;


GridEditor *newGridEditor(Grid*);

void gridEditorProcessEvent(GridEditor*, SDL_Event*);
void gridEditorUpdateOverCell(GridEditor *ge, SDL_Event *ev);
void gridEditorUpdateSelectedCell(GridEditor *ge, SDL_Event *ev);
void gridEditorUpdateFocus(GridEditor *ge, SDL_Event *ev);
void gridEditorHandleTextInput(GridEditor *ge, SDL_Event *ev);
void gridEditorShowArguments(GridEditor *ge);

// these may be used to display help for user.
void gridEditShowKeys();
void gridEditHideKeys();

