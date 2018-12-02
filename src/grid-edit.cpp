#ifndef GRID_EDITOR_C
#define GRID_EDITOR_C

#include "err.hh"
#include "grid.hh"
#include "grid-edit.hh"

GridEditor*
newGridEditor(Grid* grid) {
    GridEditor *ge = (GridEditor*)calloc(sizeof(GridEditor), 1);
    ge->grid = grid;
    ge->overCell = NULL;
    ge->selectedCell = NULL;
    ge->hasFocus = false;
    return ge;        
}

void
gridEditorUpdateFocus(GridEditor *ge, SDL_Event &ev) {
    nullDie(ge); 
    if (ev.type == SDL_MOUSEMOTION) {
        ge->hasFocus = ge->grid->containsPoint(ev.motion.x, ev.motion.y);
    } else {
        ge->hasFocus = false;
    }    
}

// states
// row select
void
gridEditorHandleTextInput(GridEditor *ge, SDL_Event &ev) {
    if (ev.type != SDL_TEXTINPUT) die("Got the wrong event type");
    switch(ev.window.event) {
    case 'q': exit(1);
    case 'r': {
        // rotate heading.
        break;
    }
    case 'a': {
        ge->grid->setSelectAllCells(true);
        break;
    }
    default: {        
    }
        
    } // end switch
}

void
gridEditorProcessEvent(GridEditor *ge, SDL_Event &ev) {
    nullDie(ge); 
    
    // hack together some spaghetti state handling and then build a
    // // state machine. Either the gridedit has focus or it doesn't.
    switch (ev.type) {
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
        
        switch (ev.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE: {
          ge->grid->setSelectAllCells(false);
        }}
        
        
        default: {
            printf("unhandled event in gridEditorProcessEvent, type: %d\n", ev.type);        
        }
            //     } 
    }}
}

void
gridEditorUpdateOverCell(GridEditor *ge, SDL_Event &ev) {
    Sint32 x = ev.motion.x;
    Sint32 y = ev.motion.y;
    ge->overCell = ge->grid->cursorCell(x, y);
    gridEditorShowArguments(ge);
    printf("Got curCell @ (%d, %d)\n", x, y);
}

void
gridEditorShowArguments(GridEditor *ge) {
    // draw arrows from the cells that contain argument.
    // clear info box.
    // draw this cell info.    
}


void
gridEditorUpdateSelectedCell(GridEditor *ge, SDL_Event &ev) {
    // if over cell is not null then use that
    // otherwise wait until there is an overcell.
    if (!ge->overCell) return;
    ge->selectedCell = ge->overCell;
    
    // select cell if deselected, deselect cell if already selected.
    ge->selectedCell->setSelect(!ge->selectedCell->selected_);
    printf("updated selected cell @ (%d, %d)\n", ge->overCell->x_, ge->overCell->y_);
}



#endif // GRID_EDITOR_C