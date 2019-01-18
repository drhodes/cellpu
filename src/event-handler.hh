#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include <functional>

using namespace std;

class EventHandler {
public:
  string m_handlerName;
  std::unordered_map<SDL_EventType, std::function<void(SDL_Event&)>> m_eventTable;
    
  EventHandler(string name);
  void registerEventHandler(SDL_EventType et, std::function<void(SDL_Event&)>);
  void handleEvent(SDL_Event &ev);
};

