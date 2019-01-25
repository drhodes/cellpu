#include <iostream>

#include "app.hh"
#include "cmdr.hh"
#include "lua.hh"

// use dependency injection to get rid of these globals
// look into http://boost-experimental.github.io/di/
LuaMgr lman;
Cmdr cmdr;

int main(void) {
  App app;
  app.eventLoop();
  std::cout << "Quitting normally. cya!" << endl;
  return 0;
}
