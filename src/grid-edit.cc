#include <memory>

#include "err.hh"
#include "grid.hh"
#include "grid-edit.hh"
#include "event-handler.hh"

GridEditor::GridEditor() :
  // inherit an event handler.
  EventHandler("GridEditor") 
{
  m_overCell = m_grid.getCell(0, 0); 
  m_selectedCell = m_grid.getCell(0, 0);
  m_hasFocus = false;
  //m_grid.executeCmd(*new GridCmdSelectCell(1, 1));
  m_statusText.setWidth(m_grid.width());
  setupEvents();
}

GridEditor::~GridEditor() {
  cerr << "destroying grid editor" << endl;
}

void
GridEditor::setupEvents() {
  
  registerEventHandler(SDL_MOUSEMOTION, 
                       [&](SDL_Event &ev) {
                         updateFocus(ev); 
                         if (!m_hasFocus) return; 
                         m_statusText.setRow(0, "Handling SDL_MOUSEMOTION");
                         updateOverCell(ev);
                       });
  
  registerEventHandler(SDL_TEXTINPUT, 
                       [&](SDL_Event &ev) {
                         if (!m_hasFocus) return;
                         string s = "Handling SDL_TEXTINPUT: ";
                         s.push_back(ev.window.event);
                           
                         m_statusText.setRow(0, s);
                         handleTextInput(ev);        
                       });

  registerEventHandler(SDL_MOUSEBUTTONDOWN,
                       [&](SDL_Event &ev) {
                         if (!m_hasFocus) return; 
                         m_statusText.setRow(0, "Handling SDL_MOUSEBUTTONDOWN");
                         updateSelectedCell(ev);
                       });
  
  registerEventHandler(SDL_KEYDOWN, 
                       [&](SDL_Event &ev) {
                         if (!m_hasFocus) return;
                         m_statusText.setRow(0, "Handling SDL_KEYDOWN");
                         
                         switch (ev.key.keysym.scancode) {
                         case SDL_SCANCODE_ESCAPE: {
                           m_grid.setSelectAllCells(false);
                           m_statusText.setRow(0, "unselected all cells");
                         }
                         default: {
                           printf("unhandled event in gridEditorProcessEvent, type: %d\n", ev.type);        
                         }}                             
                       });
}  

void
GridEditor::updateOverCell(SDL_Event &ev) {
  if (m_grid.containsPoint(ev.motion.x, ev.motion.y)) {
    m_overCell = m_grid.cursorCell(ev.motion.x, ev.motion.y);
    showArguments();
  }
}

void
GridEditor::updateSelectedCell(SDL_Event &ev) {
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
  case '?': {
    // how to message the big text box from here?
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

void
GridEditor::render() {
  m_grid.render();
  m_statusText.render();
}
