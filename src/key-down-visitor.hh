#pragma once

#include "visit.hh"

class KeyDownVisitor : public BaseVisitor 
{
private:
  SDL_Event m_ev;
public:  
  KeyDownVisitor(SDL_Event &ev) {
    m_ev = ev;
  }
  
  void visit(GridEditor &ge) {
    if (!ge.hasFocus()) return;
    ge.statusText("Handling SDL_KEYDOWN");
    
    switch (m_ev.key.keysym.scancode) {
    case SDL_SCANCODE_ESCAPE: {
      ge.setSelectAllCells(false);
      ge.statusText("unselected all cells");
    }
    default: {
      printf("unhandled event in gridEditorProcessEvent, type: %d\n", m_ev.type);
    }}     
  }
  
  void visit(Term &term) {
    if (!term.focus()) return;                         
    switch (m_ev.key.keysym.scancode) {
    case SDL_SCANCODE_BACKSPACE:
      term.popChar();
      break;
    case SDL_SCANCODE_RETURN:
    case SDL_SCANCODE_RETURN2: {
      term.doReturn();
      break;
    }
    default:
      printf("unhandled scan code\n");
      break;
    }
  }  
};
