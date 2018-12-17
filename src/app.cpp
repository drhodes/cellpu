#include <memory>

#include "app.hh"

App::App() :
  m_grid(*new Grid(12)),
  m_ge(*new GridEditor(m_grid)),

  m_termAtlas(*new Atlas("./media/Terminus.ttf", 16)),
  m_term(*new Term(m_termAtlas, 5, 750, 80, 17))
{
  m_term.put("-- Localized Processing Unit, the repl is lua.");  
}

void
App::eventLoop() {
  SDL_Event event;
  
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
      //m_grid.processEvent(event);
           
      if (event.type == SDL_KEYDOWN) {            
        if(event.key.keysym.scancode == SDL_SCANCODE_Q) {
          return;
        }
      }
    }

    m_term.render(display::getRenderer());
    m_grid.render();
    SDL_RenderPresent(display::getRenderer());
    Uint64 loopTimeStop = SDL_GetTicks();
    Uint64 delta = loopTimeStop - loopTimeStart;
    int wait = delta > 32 ? 0 : 32 - delta;
    SDL_Delay(wait);
  }
}

App::~App() {
  delete &m_grid;
  delete &m_ge;
  delete &m_termAtlas;
  delete &m_term;
}
