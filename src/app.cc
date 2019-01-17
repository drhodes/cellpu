#include <memory>
#include "app.hh"
#include "text-box.hh"
#include "select-cell.hh"

extern Cmdr cmdr; // main.cc

App::App() {
  m_term.putInput("-- Localized Processing Unit, the repl is lua.");  
}

void
App::eventLoop() {
  SDL_Event event;
  Atlas atlas("./media/Terminus.ttf", 16);
  TextBox tbox(atlas, 800, 10, 10, 10);
  tbox.setRow(0, "Is there anybody out there?");
  tbox.setRow(1, "hello?");
  
  while( true ) {
    // send app events to lua queue.
    // lua consumes events
    // lua sends messages
    // app recvs messages and acts.
    // needs to be a commander that delegates messages.
    Uint64 loopTimeStart = SDL_GetTicks();
        
    while(SDL_PollEvent(&event)) {           
      m_ge.handleEvent(event);
      m_term.handleEvent(event);
           
      if (event.type == SDL_KEYDOWN) {            
        if(event.key.keysym.scancode == SDL_SCANCODE_Q) {
          return;
        }
      }
    }
    
    while (true) {
      auto v = cmdr.frontVisitor();
      if (v.has_value()) {
        m_ge.accept(v.value());
      } else {
        break;
      }
    }
    
    SDL_SetRenderDrawColor(display::getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(display::getRenderer());
    
    m_term.render(display::getRenderer());
    m_ge.render();
    tbox.render();
    SDL_RenderPresent(display::getRenderer());
    Uint64 loopTimeStop = SDL_GetTicks();
    Uint64 delta = loopTimeStop - loopTimeStart;
    int wait = delta > 32 ? 0 : 32 - delta;
    SDL_Delay(wait);
  }
}

App::~App() {
  //delete &m_ge;
  //delete &m_term;
}
