#ifndef GRID_EDITOR_C
#define GRID_EDITOR_C

#include "err.h"
#include "grid.h"
#include "grid-edit.h"

GridEditor*
newGridEditor(Grid* grid) {
    GridEditor *ge = (GridEditor*)calloc(sizeof(GridEditor), 1);
    ge->grid = grid;
    ge->overCell = NULL;
    ge->selectedCell = NULL;
    ge->hasFocus = false;
    return ge;        
}

void gridEditorUpdateFocus(GridEditor *ge, SDL_Event *ev) {
    nullDie(ge); nullDie(ev);
    if (ev->type == SDL_MOUSEMOTION) {
        ge->hasFocus = gridContainsPoint(ge->grid, ev->motion.x, ev->motion.y);
    } else {
        ge->hasFocus = false;
    }    
}

// states
// row select
void gridEditorHandleTextInput(GridEditor *ge, SDL_Event *ev) {
    if (ev->type != SDL_TEXTINPUT) die("Got the wrong event type");
    switch(ev->window.event) {
    case 'q': exit(1);
    case 'r': {
        // rotate heading.
        break;
    }
    case 'a': {
        gridSetSelectAllCells(ge->grid, true);
        break;
    }
    default: {        
    }
        
    } // end switch
}

void gridEditorProcessEvent(GridEditor *ge, SDL_Event *ev) {
    nullDie(ge); nullDie(ev);
    
    // hack together some spaghetti state handling and then build a
    // // state machine. Either the gridedit has focus or it doesn't.
    switch (ev->type) {
    case SDL_TEXTINPUT: {        
        if (!ge->hasFocus) return;
        gridEditorHandleTextInput(ge, ev);        
        break;
    }
        
    case SDL_MOUSEMOTION: {
        gridEditorUpdateFocus(ge, ev);
        if (!ge->hasFocus) return;
        gridEditorUpdateOverCell(ge, ev);
        break;
    }
        
    case SDL_MOUSEBUTTONDOWN: {
        if (!ge->hasFocus) return;
        gridEditorUpdateSelectedCell(ge, ev);
        break;
    }
        
    case SDL_KEYDOWN: {
        if (!ge->hasFocus) return;
        
        switch (ev->key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE: {
            gridSetSelectAllCells(ge->grid, false);
        }}
        
        
        default: {
            printf("unhandled event in gridEditorProcessEvent, type: %d\n", ev->type);        
        }
            //     } 
    }}
}


void gridEditorUpdateOverCell(GridEditor *ge, SDL_Event *ev) {
    Sint32 x = ev->motion.x;
    Sint32 y = ev->motion.y;
    ge->overCell = gridCursorCell(ge->grid, x, y);
    printf("Got curCell @ (%d, %d)\n", x, y);
}

void gridEditorUpdateSelectedCell(GridEditor *ge, SDL_Event *ev) {
    // if over cell is not null then use that
    // otherwise wait until there is an overcell.
    if (!ge->overCell) return;
    ge->selectedCell = ge->overCell;
    // select if deselected, deselect if selected.
    cellSetSelect(ge->selectedCell, !ge->selectedCell->selected);
    printf("updated selected cell @ (%d, %d)\n", ge->overCell->x, ge->overCell->y);
}



#endif // GRID_EDITOR_C
