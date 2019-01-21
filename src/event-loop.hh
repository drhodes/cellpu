#include <SDL2/SDL.h>
#include "visit.hh"

class EventLoop {
private:
  void push(std::shared_ptr<Visitor> &v);

public:
  void handleAll();
  void handleTextInput(SDL_Event &ev);

};
