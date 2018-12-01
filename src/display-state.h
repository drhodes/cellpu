#ifndef DISPLAY_STATE_H
#define DISPLAY_STATE_H

#include "grid.h"

void lPutRenderer(lua_State *L, SDL_Renderer* renderer);
SDL_Renderer *lGetRenderer(lua_State *L);

void lPutFont(lua_State *L, TTF_Font* font);
TTF_Font *lGetFont(lua_State *L);

void lPutFont(lua_State *L, TTF_Font* font);
TTF_Font *lGetFont(lua_State *L);

void lPutGrid(lua_State *L, Grid *grid);
const Grid& lGetGrid(lua_State *L);


#endif // DISPLAY_STATE_H
