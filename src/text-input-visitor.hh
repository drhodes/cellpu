#pragma once

#include "visit.hh"
#include "grid-edit.hh"
#include "pan-visitor.hh"
#include "quit-visitor.hh"

extern Cmdr cmdr; // main.cc
extern LuaMgr lman; // main.cc

class TextInputVisitor : public BaseVisitor 
{
private:
  SDL_Event m_ev;
public:  
  TextInputVisitor(SDL_Event &ev) {
    m_ev = ev;
  }  
  void visit(GridEditor &ge) {
    if (ge.hasFocus()) {
      std::string key(1, (char)m_ev.window.event);
      optional<string> binding = lman.getKeyBind(key);
  
      if (binding.has_value()) {
        string visitorId = binding.value();
    
        if (visitorId == "pan-west" ||
            visitorId == "pan-east" ||
            visitorId == "pan-south" ||
            visitorId == "pan-north") {      
          cmdr.pushVisitor(make_shared<PanVisitor>(visitorId));          
        } else if (visitorId == "quit") {
          cmdr.pushVisitor(make_shared<QuitVisitor>());
        } else {
          // report error
        }
      }
    }
  }

  void visit(Term &term) {
    if (term.focus()) {
      term.pushChar(m_ev.window.event);
    }
  }

  
};
