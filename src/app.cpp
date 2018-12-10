#include <memory>

#include "app.hh"

App::App() {  
  // grid ----------------------------------------------------------------------------------------
  m_gridAtlas = make_shared<Atlas>("./media/FIXED_V0.TTF", 8);
  m_grid = make_shared<Grid>(100, 12, m_gridAtlas);
  m_ge = make_shared<GridEditor>(m_grid);
  
  // // terminal ------------------------------------------------------------------------------------
  m_termAtlas = make_shared<Atlas>("./media/Terminus.ttf", 16);
  m_term = make_shared<Term>(m_termAtlas, 5, 750, 80, 17);
  m_term->put("-- Localized Processing Unit, the repl is lua.");  
}

void
App::eventLoop() {
  SDL_Event event;
  
  while( true ) {
    Uint64 loopTimeStart = SDL_GetTicks();
        
    while(SDL_PollEvent(&event)) {           
      m_ge->processEvent(event);
      m_term->processEvent(&event);
      m_grid->processEvent(event);
           
      if (event.type == SDL_KEYDOWN) {            
        if(event.key.keysym.scancode == SDL_SCANCODE_Q) {
          return;
        }
      }
    }

    m_term->render(display::getRenderer());
    m_grid->render();
    SDL_RenderPresent(display::getRenderer());
    Uint64 loopTimeStop = SDL_GetTicks();
    Uint64 delta = loopTimeStop - loopTimeStart;
    int wait = delta > 32 ? 0 : 32 - delta;
    SDL_Delay(wait);
  }
}
