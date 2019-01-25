#include <string>

#include "callbacks.hh"
#include "err.hh"
#include "lua.hh"

LuaMgr::LuaMgr() {
  // init global state.
  _LS = luaL_newstate();
  nullDie(_LS);

  luaL_openlibs(_LS);   // opens Lua
  luaopen_base(_LS);    // opens the basic library
  luaopen_table(_LS);   // opens the table library
  luaopen_io(_LS);      // opens the I/O library
  luaopen_string(_LS);  // opens the string lib.
  luaopen_math(_LS);    // opens the math lib.

  registerAllCallbacks();
  doFile("./lua/keyboard-cfg.lua");
}

LuaMgr::~LuaMgr() { lua_close(_LS); }

lua_State* LuaMgr::getLuaState() { return _LS; }

void LuaMgr::bindKey(string key, string cmd) {
  m_keybindings.bindKey(key, cmd);
}

optional<string> LuaMgr::getKeyBind(string key) {
  return m_keybindings.getKeyBind(key);
}

void LuaMgr::doFile(const char* filename) {
  int err = luaL_dofile(_LS, filename);
  if (err) {
    std::cerr << lua_tostring(_LS, -1);
    perr(lua_tostring(_LS, -1));
    lua_pop(_LS, 1);  // pop error message from the stack
  }
}

string LuaMgr::doLine(std::string line) {
  int err = luaL_loadbuffer(_LS, line.c_str(), line.length(), "line") ||
            lua_pcall(_LS, 0, 0, 0);
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

void LuaMgr::registerAllCallbacks() {
  registerCallback("selectCell", callback::lSelectCell);
  registerCallback("dump", callback::lDump);
  registerCallback("zoom", callback::lZoomGrid);
  registerCallback("bindKey", callback::lBindKey);
  registerCallback("getKeyBind", callback::lGetKeyBind);
}

void LuaMgr::registerCallback(string funcname, lua_CFunction func) {
  // What kind of invariants need to hold here?
  lua_pushcfunction(_LS, func);
  lua_setglobal(_LS, funcname.c_str());
  lua_pop(_LS, 1);
}
