#include <memory>

#include "app.hh"
#include "bbox.hh"
#include "event-loop.hh"
#include "global.hh"
#include "instruction-selector.hh"
#include "render-visitor.hh"
#include "select-cell.hh"
#include "text-box.hh"

App::App() {
  m_term.putInput("-- Localized Processing Unit, the repl is lua.");
}

void
App::eventLoop() {
  Atlas atlas("./media/Terminus.ttf", 16);
  EventLoop eventLoop;

  while (m_running) {
    Uint64 loopTimeStart = SDL_GetTicks();
    eventLoop.handleAll();

    while (true) {
      // consume visitors.
      auto v = global::cmdr().frontVisitor();
      if (v) {
        accept(v.value());
      } else {
        break;
      }
    }

    SDL_SetRenderDrawColor(display::getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(display::getRenderer());

    m_ge.render();
    m_term.render(display::getRenderer());
    m_instSel.render(display::getRenderer());

    SDL_RenderPresent(display::getRenderer());
    Uint64 loopTimeStop = SDL_GetTicks();
    Uint64 delta = loopTimeStop - loopTimeStart;
    int wait = delta > 32 ? 0 : 32 - delta;
    SDL_Delay(wait);
  }
}

void
App::accept(std::shared_ptr<Visitor> v) {
  m_instSel.accept(v);
  m_term.accept(v);
  m_ge.accept(v);
  v->visit(*this);
}

// IEntity
void
App::quit() {
  m_running = false;
}

bool
App::hasFocus() {
  return false;
}

IEntity&
App::parent() {
  return *this;
}

BBox&
App::bbox() {
  return m_bbox;
}

int
App::zIndex() {
  return 0;  // bottom of pile
}

void
App::hidden(bool b) {
  m_hidden = b;
}

bool
App::hidden() {
  return m_hidden;
}
