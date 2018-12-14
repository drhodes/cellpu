#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include <functional>

using namespace std;

//typedef std::function<void(SDL_Event&)> SDL_handler

class EventHandler {
public:
  std::unordered_map<SDL_EventType, std::function<void(SDL_Event&)>> m_eventTable;
    
  EventHandler();
  void registerEventHandler(SDL_EventType et, std::function<void(SDL_Event&)>);
  void handleEvent(SDL_Event &ev);
};

