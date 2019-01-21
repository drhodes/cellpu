#include <SDL2/SDL.h>

// catch events.
// use lua keybindings (./lua/keyboard-cfg.lua)
// see lua.hh for c++ interface
// to push appropriate visitors onto the cmdr queue which
// is consumed in app.cc
#include "event-loop.hh"
#include "quit-visitor.hh"
#include "pan-visitor.hh"

extern LuaMgr lman;  
extern Cmdr cmdr;

void
EventLoop::handleAll() {
  SDL_Event event;
  
  while(SDL_PollEvent(&event)) {
    // REFACTORING.
    // GridEdit::handleEvent is going away.  
    // m_ge.handleEvent(event);
    // m_term.handleEvent(event);
    
    if (event.type == SDL_KEYDOWN) {      
    } else if (event.type == SDL_TEXTINPUT) {
      handleTextInput(event);
    }
  }
}

void
EventLoop::handleTextInput(SDL_Event &ev) {
  std::string key(1, (char)ev.window.event);
  optional<string> binding = lman.getKeyBind(key);
  
  if (binding.has_value()) {
    string visitorId = binding.value();

    // Yes, using strings here is not ideal.
    // better to use enums, but these values are coming from lua.
    // TODO: consider these type safer
    
    if (false) {
    } else if (visitorId == "pan-west" ||
               visitorId == "pan-east" ||
               visitorId == "pan-south" ||
               visitorId == "pan-north") {      
      cmdr.pushVisitor(make_shared<PanVisitor>(visitorId));
      
    } else if (visitorId == "quit") {
      cmdr.pushVisitor(make_shared<QuitVisitor>());
      
    } else {      
      // report error
    }
    
    // if (!m_hasFocus) return;
    // string s = "Handling SDL_TEXTINPUT: ";
    // s.push_back(ev.window.event);
    // m_statusText.setRow(0, s);
    // handleTextInput(ev);        
    //                      });
  }
}

void
EventLoop::push(shared_ptr<Visitor> &v) {
  //cmdr.pushVisitor(v)
}
