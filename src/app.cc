#include <memory>

#include "app.hh"
#include "event-loop.hh"
#include "instruction-selector.hh"
#include "select-cell.hh"
#include "text-box.hh"
#include "global.hh"

App::App() {
  m_term.putInput("-- Localized Processing Unit, the repl is lua.");
}

void App::eventLoop() {
  Atlas atlas("./media/Terminus.ttf", 16);
  TextBox tbox(atlas, 800, 10, 10, 10);
  EventLoop eventLoop;

  tbox.setRow(0, "Is there anybody out there?");
  tbox.setRow(1, "hello?");

  while (m_running) {
    Uint64 loopTimeStart = SDL_GetTicks();
    eventLoop.handleAll();
    
    while (true) {
      // consume visitors.
      auto v = global::cmdr().frontVisitor();
      if (v.has_value()) {
        accept(v.value());
      } else {
        break;
      }
    }

    SDL_SetRenderDrawColor(display::getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(display::getRenderer());
    
    m_ge.render();
    tbox.render();    
    m_term.render(display::getRenderer());
    m_instSel.render(display::getRenderer());
    
    SDL_RenderPresent(display::getRenderer());
    Uint64 loopTimeStop = SDL_GetTicks();
    Uint64 delta = loopTimeStop - loopTimeStart;
    int wait = delta > 32 ? 0 : 32 - delta;
    SDL_Delay(wait);
  }
}

void App::accept(std::shared_ptr<Visitor> v) {
  m_instSel.accept(v);
  m_term.accept(v);
  m_ge.accept(v);
  v->visit(*this);
}

void App::quit() { m_running = false; }
