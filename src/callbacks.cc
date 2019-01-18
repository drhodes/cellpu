// @file
// @brief This file is marvelous.

// C callbacks for lua -----------------------------------------------------------------------------

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "callbacks.hh"
#include "err.hh"
#include "grid.hh"
#include "cell.hh"
#include "lua.hh"
#include "cmdr.hh"
#include "select-cell.hh"
#include "zoom-grid.hh"

extern LuaMgr& lman;  
extern Cmdr cmdr;  

using namespace std;

namespace callback {
  
  int
  lSelectCell(lua_State *L) {
    int x = lua_tonumber(L, 1);
    int y = lua_tonumber(L, 2);
    lua_pop(L, 2);
    cmdr.pushVisitor(make_shared<SelectCellVisitor>(x, y));
    return 0;
  }

  int
  lZoomGrid(lua_State *L) {
    int factor = lua_tonumber(L, 1);
    lua_pop(L, 1);
    cmdr.pushVisitor(make_shared<ZoomGridVisitor>(factor));
    return 0;
  }
  
  int
  lDump(lua_State *L) {
    _estack.dump();
    return 0;
  }
  
}
