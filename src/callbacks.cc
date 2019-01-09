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

extern LuaMgr& lman;  

namespace callback {

  int
  lSelectCell(lua_State *L) {
    int x = lua_tonumber(L, 1);
    int y = lua_tonumber(L, 2);
    lua_pop(L, 2);
    
    const Grid &grid = lman.getGrid();    
    auto cell = grid.getCell(x, y);
    cell->setSelect(true);
    return 0;
  }
  
  int
  lDump(lua_State *L) {
    _estack.dump();
    return 0;
  }
}
