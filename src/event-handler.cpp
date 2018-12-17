#include <string>
#include <iostream>

#include "event-handler.hh"

using namespace std;

EventHandler::EventHandler(string name) {
  m_handlerName = name;
}

void
EventHandler::registerEventHandler(SDL_EventType et, std::function<void(SDL_Event&)> f) {
  cerr << "Register event: " << et << " for: " << m_handlerName << endl;
  m_eventTable[et] = f;
}

void
EventHandler::handleEvent(SDL_Event &ev) {
  auto tup = m_eventTable.find((SDL_EventType)(ev.type));
  if (tup == std::end(m_eventTable)) {
    cerr << "unhandled event in handler: " << m_handlerName << endl;
  } else {
    tup->second(ev);
  }
}
