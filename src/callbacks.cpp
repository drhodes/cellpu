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

#include "callbacks.h"
#include "err.h"
#include "grid.h"
#include "cell.h"


namespace callback {
  int
  lClear(lua_State *L) {
    // get the renderer pointer from lua.
    SDL_Renderer *renderer = lGetRenderer(L);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return 0;
  }

  int
  lSetColor(lua_State *L) {
    int r = lua_tonumber(L, 1);
    int g = lua_tonumber(L, 2);
    int b = lua_tonumber(L, 3);
    int a = lua_tonumber(L, 4);
    lua_pop(L, 4);
    
    SDL_Renderer *renderer = lGetRenderer(L);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    return 0;
  }


  int
  lDrawBox(lua_State *L) {
    int x = lua_tonumber(L, 1);
    int y = lua_tonumber(L, 2);
    int h = lua_tonumber(L, 3);
    int w = lua_tonumber(L, 4);
    lua_pop(L, 4);
    
    SDL_Renderer *renderer = lGetRenderer(L);
    SDL_Rect rect = { x, y, h, w};
    SDL_RenderFillRect(renderer, &rect);
    return 0;
  }

  int
  lUpdate(lua_State *L) {
    //get the renderer pointer from lua.
    SDL_Renderer *renderer = lGetRenderer(L);
    SDL_RenderPresent(renderer);
    return 0;
  }

  int
  lSelectCell(lua_State *L) {
    int x = lua_tonumber(L, 1);
    int y = lua_tonumber(L, 2);
    lua_pop(L, 2);
    
    Grid *grid = lGetGrid(L);    
    Cell *cell = gridGetCell(grid, x, y);
    if (cell==NULL) {        
      luaL_error(L, _estack.topMsg().c_str()); 
      return 1;
    }
    
    cell->setSelect(true);
    return 0;
  }

  int
  lDump(lua_State *L) {
    _estack.dump();
    return 0;
  }


  void
  register_all(lua_State *L) {
    // clear the renderer
    lua_pushcfunction(L, lClear);
    lua_setglobal(L, "clear");

    lua_pushcfunction(L, lSetColor);
    lua_setglobal(L, "setColor");

    lua_pushcfunction(L, lDrawBox);
    lua_setglobal(L, "drawBox");

    lua_pushcfunction(L, lUpdate);
    lua_setglobal(L, "update");
    
    lua_pushcfunction(L, lSelectCell);
    lua_setglobal(L, "selectCell");

    lua_pushcfunction(L, lDump);
    lua_setglobal(L, "dump");

    
    lua_pop(L, 6);
  }
}
