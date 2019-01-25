#include <SDL2/SDL.h>

// catch events.
// use lua keybindings (./lua/keyboard-cfg.lua)
// see lua.hh for c++ interface
// to push appropriate visitors onto the cmdr queue which
// is consumed in app.cc

#include "event-loop.hh"
#include "key-down-visitor.hh"
#include "mouse-button-down-visitor.hh"
#include "mouse-motion-visitor.hh"
#include "text-input-visitor.hh"

extern LuaMgr lman;
extern Cmdr cmdr;

void EventLoop::handleAll() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_KEYDOWN) {
      cmdr.pushVisitor(make_shared<KeyDownVisitor>(event));
    } else if (event.type == SDL_TEXTINPUT) {
      cmdr.pushVisitor(make_shared<TextInputVisitor>(event));
    } else if (event.type == SDL_MOUSEMOTION) {
      cmdr.pushVisitor(make_shared<MouseMotionVisitor>(event));
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
      cmdr.pushVisitor(make_shared<MouseButtonDownVisitor>(event));
    } else {
      // unhandled event type.
    }
  }
}
