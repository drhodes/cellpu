#include <memory>

#include "err.hh"
#include "grid.hh"
#include "grid-edit.hh"
#include "event-handler.hh"

GridEditor::GridEditor() :
  EventHandler("GridEditor") 
{
  m_overCell = m_grid.getCell(0, 0); 
  m_selectedCell = m_grid.getCell(0, 0);
  m_hasFocus = false;
  m_statusText.setWidth(m_grid.width());
  setupEvents();
}

GridEditor::~GridEditor() {
  cerr << "destroying grid editor" << endl;  
  delete &m_grid;
  delete &m_statusText;
}

void
GridEditor::accept(std::shared_ptr<Visitor> v) {
  v->visit(*this);
  m_grid.accept(v);
}

void
GridEditor::panEast() {
  cout << "[STUB] panning East" << endl;
}

void
GridEditor::panWest() {
  cout << "[STUB] panning West" << endl;
}

void
GridEditor::panNorth() {
  cout << "[STUB] panning North" << endl;
}

void
GridEditor::panSouth() {
  cout << "[STUB] panning South" << endl;
}

void
GridEditor::setupEvents() {
  registerEventHandler(SDL_MOUSEBUTTONDOWN,
                       [&](SDL_Event &ev) {
                         if (!m_hasFocus) return; 
                         m_statusText.setRow(0, "Handling SDL_MOUSEBUTTONDOWN");
                         updateSelectedCell(ev);
                       });
}

void
GridEditor::statusText(string msg) {
  m_statusText.setRow(0, msg);
}

void
GridEditor::setSelectAllCells(bool b) {
  m_grid.setSelectAllCells(b);
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
  m_selectedCell->selected(!m_selectedCell->selected());
}

void
GridEditor::updateFocus(SDL_Event &ev) {
  if (ev.type == SDL_MOUSEMOTION) {
    m_hasFocus = m_grid.containsPoint(ev.motion.x, ev.motion.y);
  } else {
    m_hasFocus = false;
  }    
}

bool
GridEditor::hasFocus() {
  return m_hasFocus;
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
    
  case 'w': {
    panNorth();
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
