#include <string>

//c#include "callbacks.hh"
#include "lua.hh"
#include "err.hh"
#include "callbacks.hh"

LuaMgr::LuaMgr() {
  // init global state.
  _LS = luaL_newstate();
  nullDie(_LS);
  
  luaL_openlibs(_LS);          // opens Lua 
  luaopen_base(_LS);           // opens the basic library
  luaopen_table(_LS);          // opens the table library 
  luaopen_io(_LS);             // opens the I/O library 
  luaopen_string(_LS);         // opens the string lib. 
  luaopen_math(_LS);           // opens the math lib.

  register_callbacks();
}

LuaMgr::~LuaMgr() {
  lua_close(_LS);
}

lua_State*
LuaMgr::getLuaState() {
  return _LS;
}

void
LuaMgr::doFile(const char *filename) {  
  int err = luaL_dofile(_LS, filename);
  if (err) {
    fprintf(stderr, "%s\n", lua_tostring(_LS, -1));
    perr(lua_tostring(_LS, -1));
    lua_pop(_LS, 1);  // pop error message from the stack 
  }
}

string
LuaMgr::doLine(std::string line) {
  int err = luaL_loadbuffer(_LS, line.c_str(), line.length(), "line") || lua_pcall(_LS, 0, 0, 0);
  string s("");
  
  if (err) {
    string errStr(lua_tostring(_LS, -1));
    fprintf(stderr, "%s\n", lua_tostring(_LS, -1));
    s += string(lua_tostring(_LS, -1));
    perr(errStr);
    lua_pop(_LS, 1);    
  }
  return s;
}

// managing the grid -------------------------------------------------------------------------------

void
LuaMgr::putGrid(Grid *grid) {
  lua_pushinteger(_LS, (uintptr_t)grid);
  lua_setglobal(_LS, "grid");
}

const Grid&
LuaMgr::getGrid() {
  // fetch the pointer to grid and place at top of stack.
  lua_getglobal(_LS, "grid"); 
  
  // get top of stack and coerce to pointer type.    
  uintptr_t *ptr2 = new uintptr_t;
  *ptr2 = (uintptr_t)lua_tointeger(_LS, -1);
  lua_pop(_LS, 1);
  return reinterpret_cast<const Grid&>(*ptr2);
}

void
LuaMgr::register_callbacks() {    
  lua_pushcfunction(_LS, callback::lSelectCell);
  lua_setglobal(_LS, "selectCell");

  lua_pushcfunction(_LS, callback::lDump);
  lua_setglobal(_LS, "dump");
  
  auto sum = [] (lua_State *L) {
               cout << "Hey!" << endl;
               return 0;
             };
  
  lua_pushcfunction(_LS, sum);
  lua_setglobal(_LS, "sum");
  lua_pop(_LS, 6);
}
