
#include <string>
#include <iostream>

#include "event-handler.hh"

using namespace std;

EventHandler::EventHandler() {}


void
EventHandler::registerEventHandler(SDL_EventType et, std::function<void(SDL_Event&)> f) {
  cerr << "Register event: " << et << endl;
  m_eventTable[et] = f;
}

void
EventHandler::handleEvent(SDL_Event &ev) {
  auto tup = m_eventTable.find((SDL_EventType)(ev.type));
  if (tup == std::end(m_eventTable)) {
    cerr << "unhandled event in Term." << endl;
  } else {
    tup->second(ev);
  }
}

  // EventHandler();
  // void registerEventHandler(SDL_EventType et, auto f);
  // void handleEvent(SDL_Event &ev);
