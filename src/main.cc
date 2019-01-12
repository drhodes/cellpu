#include "app.hh"
#include "lua.hh"
#include "cmdr.hh"

LuaMgr lman;
Cmdr cmdr;


int main (void) {
  App app;
  //lman.register_app(app);
  app.eventLoop();
  return 0;
}
