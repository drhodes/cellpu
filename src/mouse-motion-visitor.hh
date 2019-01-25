#pragma once

#include "grid-edit.hh"
#include "term.hh"
#include "visit.hh"

extern Cmdr cmdr;    // main.cc
extern LuaMgr lman;  // main.cc

class MouseMotionVisitor : public BaseVisitor {
 private:
  SDL_Event m_ev;

 public:
  MouseMotionVisitor(SDL_Event &ev) { m_ev = ev; }

  void visit(GridEditor &ge) {
    ge.updateFocus(m_ev);
    if (!ge.hasFocus()) return;
    ge.statusText("Handling SDL_MOUSEMOTION");
    ge.updateOverCell(m_ev);
  }

  void visit(Term &term) { term.updateFocus(m_ev); }
};
