// @file
// @brief This file is marvelous.

#ifndef DISPLAY_STATE_C
#define DISPLAY_STATE_C

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <stdbool.h> 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err.hh"
#include "display-state.hh"
#include "grid.hh"

// global state ------------------------------------------------------------------------------------

// SDL_Window *window = NULL;
// SDL_Renderer *renderer = NULL;

// managing the SDL renderer state in lua. ---------------------------------------------------------

void
lPutRenderer(lua_State *L, SDL_Renderer *renderer)
{
    lua_pushinteger(L, (uintptr_t)renderer);
    lua_setglobal(L, "renderer");
}

SDL_Renderer
*lGetRenderer(lua_State *L)
{
    // fetch the pointer to renderer and place at top of stack.
    lua_getglobal(L, "renderer");
    // get top of stack and coerce to pointer type.
    uintptr_t ptr2 = (uintptr_t)lua_tointeger(L, -1);
    lua_pop(L, 1);
    return (SDL_Renderer*)ptr2;
}

// managing the SDL font state in lua. ---------------------------------------------------------

void
lPutFont(lua_State *L, TTF_Font *font)
{
    lua_pushinteger(L, (uintptr_t)font);
    lua_setglobal(L, "font");
}

TTF_Font
*lGetFont(lua_State *L)
{
    // fetch the pointer to font and place at top of stack.
    lua_getglobal(L, "font");
    // get top of stack and coerce to pointer type.
    uintptr_t ptr2 = (uintptr_t)lua_tointeger(L, -1);
    lua_pop(L, 1);
    return (TTF_Font*)ptr2;
}

// managing the grid -------------------------------------------------------------------------------

void
lPutGrid(lua_State *L, Grid *grid) {
    lua_pushinteger(L, (uintptr_t)grid);
    lua_setglobal(L, "grid");
}

const Grid&
lGetGrid(lua_State *L) {
  // fetch the pointer to grid and place at top of stack.
  lua_getglobal(L, "grid"); 
  
  // get top of stack and coerce to pointer type.    
  uintptr_t *ptr2 = new uintptr_t;
  *ptr2 = (uintptr_t)lua_tointeger(L, -1);
  lua_pop(L, 1);
  return reinterpret_cast<const Grid&>(*ptr2);
}


#endif // DISPLAY_STATE_C
