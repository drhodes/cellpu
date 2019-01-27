#pragma once

#include "grid-edit.hh"
#include "instruction.hh"
#include "pan-visitor.hh"
#include "quit-visitor.hh"
#include "visit.hh"

extern Cmdr cmdr;    // main.cc
extern LuaMgr lman;  // main.cc

class TextInputVisitor : public BaseVisitor {
 private:
  SDL_Event m_ev;

 public:
  TextInputVisitor(SDL_Event &ev) { m_ev = ev; }

  void visit(GridEditor &ge) {
    if (!bubbleEvent()) return;

    if (ge.hasFocus()) {
      auto binding = getBinding();

      if (binding.has_value()) {
        string visitorId = binding.value();

        if (visitorId == "pan-west" || visitorId == "pan-east" ||
            visitorId == "pan-south" || visitorId == "pan-north") {
          cmdr.pushVisitor(make_shared<PanVisitor>(visitorId));

        } else if (visitorId == "zoom-in") {
          ge.statusText("zooming in: " + visitorId);
          ge.zoomIn();
        } else if (visitorId == "zoom-out") {
          ge.zoomOut();
        } else {
          // report error
          ge.statusText("unhandled binding: " + visitorId);
        }
      } else {
        std::string key(1, (char)m_ev.window.event);
        ge.statusText("key not bound: " + key);
      }
    }
  }

  void visit(Term &term) {
    if (!bubbleEvent()) return;

    if (term.focus()) {
      // prevent event from bubbling out.
      bubbleEvent(false);
      term.pushChar(m_ev.window.event);
    }
  }

  void visit(App &app) {
    if (!bubbleEvent()) return;

    auto binding = getBinding();
    if (binding.has_value()) {
      if (binding.value() == "quit") {
        app.quit();
      }
    }
  }

  void visit(InstructionSelector &is) {
    if (!bubbleEvent()) return;
    if (is.focus()) bubbleEvent(false);

    auto binding = getBinding();
    if (binding.has_value()) {
      string visitorId = binding.value();
      if (visitorId == "noop-instruction") {
      }
    }
  }

  optional<string> getBinding() {
    std::string key(1, (char)m_ev.window.event);
    return lman.getKeyBind(key);
  }
};
