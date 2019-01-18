#pragma once

#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>

#include <SDL2/SDL_ttf.h>

#include <string>
#include <map>

#include "keybinding.hh"

using namespace std;

class Grid;

class LuaMgr {
private:
  lua_State *_LS = nullptr;
  KeyBindings m_keybindings;
  
public:  
  LuaMgr();
  ~LuaMgr();
  
  void doFile(const char *filename);
  string doLine(std::string);

  lua_State* getLuaState(); // this is unfortunate.

  void bindKey(string key, string cmd);
  string getKeyBind(string key);
  
  int putL(lua_State *L);
  
  void registerCallback(string funcname, lua_CFunction func);
  void registerAllCallbacks();
};
