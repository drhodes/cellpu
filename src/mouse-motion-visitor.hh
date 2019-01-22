#pragma once

#include "visit.hh"
#include "grid-edit.hh"
#include "term.hh"

extern Cmdr cmdr; // main.cc
extern LuaMgr lman; // main.cc

class MouseMotionVisitor : public BaseVisitor 
{
private:
  SDL_Event m_ev;
public:  
  MouseMotionVisitor(SDL_Event &ev) {    
    m_ev = ev;
  }
  
  void visit(GridEditor &ge) {
    ge.updateFocus(m_ev); 
    if (!ge.hasFocus()) return;
    ge.statusText("Handling SDL_MOUSEMOTION");
    ge.updateOverCell(m_ev);
  }

  void visit(Term &term) {
    Sint32 x = m_ev.motion.x;
    Sint32 y = m_ev.motion.y;        
    term.focus(term.containsPx(x, y));
  }
  
};