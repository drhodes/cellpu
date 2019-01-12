#pragma once

#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>

#include <SDL2/SDL_ttf.h>

#include <string>

using namespace std;

class Grid;

class LuaMgr {
private:
  lua_State *_LS = nullptr;  
  
public:  
  LuaMgr();
  ~LuaMgr();
  
  void doFile(const char *filename);
  string doLine(std::string);

  lua_State* getLuaState(); // this is unfortunate.
  
  int putL(lua_State *L);
  
  void putGrid(Grid *grid);
  const Grid& getGrid();
  
  void register_callbacks();
};
