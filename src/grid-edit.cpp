#include "err.hh"
#include "grid.hh"
#include "grid-edit.hh"


GridEditor::GridEditor(Grid &grid) :
  m_grid(grid),
  m_overCell(grid.getCell(0, 0)),
  m_selectedCell(grid.getCell(0, 0))
{
  m_hasFocus = false;
}

GridEditor::~GridEditor() {
  cerr << "destroying grid editor" << endl;
}

void
GridEditor::processEvent(SDL_Event &ev) {
  // hack together some spaghetti state handling and then build a
  // state machine. Either the gridedit has focus or it doesn't.
  
  switch (ev.type) {
  case SDL_TEXTINPUT: {        
    if (!m_hasFocus) return;
    handleTextInput(ev);        
    break;
  }
        
  case SDL_MOUSEMOTION: {
    updateFocus(ev);
    if (!m_hasFocus) return;
    updateOverCell(ev);
    break;
  }
        
  case SDL_MOUSEBUTTONDOWN: {
    if (!m_hasFocus) return;
    updateSelectedCell(ev);
    break;
  }
        
  case SDL_KEYDOWN: {
    if (!m_hasFocus) return;
        
    switch (ev.key.keysym.scancode) {
    case SDL_SCANCODE_ESCAPE: {
      m_grid.setSelectAllCells(false);
    }}
        
    default: {
      printf("unhandled event in gridEditorProcessEvent, type: %d\n", ev.type);        
    }
      //     } 
  }}
}

void
GridEditor::updateOverCell(SDL_Event &ev) {
  m_overCell = m_grid.cursorCell(ev.motion.x, ev.motion.y);
  showArguments();
}

void
GridEditor::updateSelectedCell(SDL_Event &ev) {
  // otherwise wait until there is an overcell.
  m_selectedCell = m_overCell;
    
  // select cell if deselected, deselect cell if already selected.
  m_selectedCell->setSelect(!m_selectedCell->selected_);
}

void
GridEditor::updateFocus(SDL_Event &ev) {
  if (ev.type == SDL_MOUSEMOTION) {
    m_hasFocus = m_grid.containsPoint(ev.motion.x, ev.motion.y);
  } else {
    m_hasFocus = false;
  }    
}

void
GridEditor::handleTextInput(SDL_Event &ev) {
  // this handles input for visible text chars, not the esc key, etc.
  // there will be a state machine here the grid editor will have
  // modes.
  
  if (ev.type != SDL_TEXTINPUT) die("Got the wrong event type");
  switch(ev.window.event) {
    
  case 'r': {
    // rotate heading.
    break;
  }
  case 'a': {
    m_grid.setSelectAllCells(true);
    break;
  }
    
  default: {
    // complain about no keybinding.
  }} // end switch
}

void
GridEditor::showArguments() {
  // draw arrows from the cells that contain argument.
  // clear info box.
  // draw this cell info.      
}


