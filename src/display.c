// #include <stdio.h>
// #include <string.h>
// #include <lua5.3/lua.h>
// #include <lua5.3/lauxlib.h>
// #include <lua5.3/lualib.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL.h>
// #include <stdlib.h>
// #include <stdbool.h> 
// #include <stdint.h>
// #include <assert.h>

// // managing the SDL renderer state in lua. ---------------------------------------------------------

// void lPutRenderer(lua_State *L, SDL_Renderer* renderer) {
//     lua_pushinteger(L, (uintptr_t)renderer);
//     lua_setglobal(L, "renderer");
// }

// SDL_Renderer* lGetRenderer(lua_State *L) {
//     // fetch the pointer to renderer and place at top of stack.
//     lua_getglobal(L, "renderer");
//     // get top of stack and coerce to pointer type.
//     uintptr_t ptr2 = (uintptr_t)lua_tointeger(L, -1);    
//     return (SDL_Renderer*)ptr2;
// }

// // C callbacks for lua -----------------------------------------------------------------------------

// static int l_clear(lua_State *L) {
//     //get the renderer pointer from lua.
//     SDL_Renderer *renderer = lGetRenderer(L);
//     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//     SDL_RenderClear(renderer);
//     SDL_RenderPresent(renderer);
//     return 0;
// }



// }




