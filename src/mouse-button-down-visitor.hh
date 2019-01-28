#pragma once

#include "grid-edit.hh"
#include "instruction-selector.hh"
#include "lua.hh"
#include "visit.hh"

class MouseButtonDownVisitor : public BaseVisitor {
 private:
  SDL_Event m_ev;

 public:
  MouseButtonDownVisitor(SDL_Event &ev) { m_ev = ev; }

  void visit(GridEditor &ge) {
    if (!bubbleEvent()) return;
    if (!ge.hasFocus()) return;
    ge.statusText("Handling SDL_MOUSEDOWN");
    ge.toggleSelectCurCell(m_ev);
  }

  void visit(InstructionSelector &is) {
    if (!bubbleEvent()) return;
    if (is.focus()) {
      bubbleEvent(false);
    }
  }
};
