#include "app.hh"
#include "lua.hh"

LuaMgr lman;

int main (void) {
  App app;
  app.eventLoop();
  
  return 0;
}
