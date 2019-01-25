#include <memory>

#include "err.hh"
#include "grid.hh"
#include "grid-edit.hh"
#include "event-handler.hh"

GridEditor::GridEditor() {
  m_overCell = m_grid.getCell(0, 0); 
  m_hasFocus = false;
  m_statusText.setWidth(m_grid.width());
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
GridEditor::setSelectedCellsInstruction(shared_ptr<Instruction> inst) {
  auto cells = m_grid.getAllSelectedCells();
  for (auto cell : cells) {
    cell->setInstruction(inst);
  }
}

void
GridEditor::toggleSelectCurCell(SDL_Event &ev) {
  shared_ptr<Cell> cell = m_grid.cursorCell(ev.motion.x, ev.motion.y);
  cell->selected(!cell->selected());
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
