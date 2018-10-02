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

#include "err.h"
// managing the SDL renderer state in lua. ---------------------------------------------------------

void lPutRenderer(lua_State *L, SDL_Renderer* renderer) {
    lua_pushinteger(L, (uintptr_t)renderer);
    lua_setglobal(L, "renderer");
}

SDL_Renderer* lGetRenderer(lua_State *L) {
    // fetch the pointer to renderer and place at top of stack.
    lua_getglobal(L, "renderer");
    // get top of stack and coerce to pointer type.
    uintptr_t ptr2 = (uintptr_t)lua_tointeger(L, -1);
    lua_pop(L, 1);
    return (SDL_Renderer*)ptr2;
}

// managing the SDL font state in lua. ---------------------------------------------------------

void lPutFont(lua_State *L, TTF_Font* font) {
    lua_pushinteger(L, (uintptr_t)font);
    lua_setglobal(L, "font");
}

TTF_Font* lGetFont(lua_State *L) {
    // fetch the pointer to font and place at top of stack.
    lua_getglobal(L, "font");
    // get top of stack and coerce to pointer type.
    uintptr_t ptr2 = (uintptr_t)lua_tointeger(L, -1);
    lua_pop(L, 1);
    return (TTF_Font*)ptr2;
}


// C callbacks for lua -----------------------------------------------------------------------------

static int lClear(lua_State *L) {
    //get the renderer pointer from lua.
    SDL_Renderer *renderer = lGetRenderer(L);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return 0;
}

static int lSetColor(lua_State *L) {
    int r = lua_tonumber(L, 1);  /* get argument */
    int g = lua_tonumber(L, 2);  /* get argument */
    int b = lua_tonumber(L, 3);  /* get argument */
    int a = lua_tonumber(L, 4);  /* get argument */
    lua_pop(L, 4);
    
    SDL_Renderer *renderer = lGetRenderer(L);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    return 0;
}


static int lDrawBox(lua_State *L) {
    int x = lua_tonumber(L, 1);  /* get argument */
    int y = lua_tonumber(L, 2);  /* get argument */
    int h = lua_tonumber(L, 3);  /* get argument */
    int w = lua_tonumber(L, 4);  /* get argument */
    lua_pop(L, 4);
    
    SDL_Renderer *renderer = lGetRenderer(L);
    SDL_Rect rect = { x, y, h, w};
    SDL_RenderFillRect(renderer, &rect);
    return 0;
}

static int lDrawText(lua_State *L) {
    int x = lua_tonumber(L, 1);  /* get argument */
    int y = lua_tonumber(L, 2);  /* get argument */
    const char *msgString = lua_tostring(L, 3);  // change to string.
    lua_pop(L, 2);

    SDL_Renderer *renderer = lGetRenderer(L);
    TTF_Font *font = lGetFont(L);

    SDL_Color white = {255, 255, 255};
    SDL_Surface* surfaceTxt = TTF_RenderText_Solid(font, msgString, white);
    SDL_Texture* msg = SDL_CreateTextureFromSurface(renderer, surfaceTxt);
    
    int msgW = 0;
    int msgH = 0;
    SDL_QueryTexture(msg, NULL, NULL, &msgW, &msgH);
    
    SDL_Rect msgRect = { x, y, msgW, msgH };
    SDL_RenderCopy(renderer, msg, NULL, &msgRect);
    return 0;
}


static int lUpdate(lua_State *L) {
    //get the renderer pointer from lua.
    SDL_Renderer *renderer = lGetRenderer(L);
    SDL_RenderPresent(renderer);
    return 0;
}


// Register callbacks ------------------------------------------------------------------------------

void register_callbacks(lua_State *L) {
    // clear the renderer
    lua_pushcfunction(L, lClear);
    lua_setglobal(L, "clear");

    lua_pushcfunction(L, lSetColor);
    lua_setglobal(L, "setColor");

    lua_pushcfunction(L, lDrawBox);
    lua_setglobal(L, "drawBox");

    lua_pushcfunction(L, lUpdate);
    lua_setglobal(L, "update");
    
    lua_pushcfunction(L, lDrawText);
    lua_setglobal(L, "drawText");

    
    lua_pop(L, 4);
}

int main (void) {
    SDL_Init(SDL_INIT_VIDEO);            
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    
    window = SDL_CreateWindow( "proc sim",                // window title
                               SDL_WINDOWPOS_UNDEFINED,   // initial x position
                               SDL_WINDOWPOS_UNDEFINED,   // initial y position
                               800,                       // width, in pixels
                               800,                       // height, in pixels
                               SDL_WINDOW_OPENGL          // flags - see below
                               );
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    
    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        perr("Could not create window"); perr(SDL_GetError());
        return 1;
    }

    // font ----------------------------------------------------------------------------------------
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("./media/Inconsolata-g.ttf", 16);
    // SDL_Color white = {255, 255, 255};
    // SDL_Surface* surfaceTxt = TTF_RenderText_Solid(font, "msg", white);
    // SDL_Texture* msg = SDL_CreateTextureFromSurface(renderer, surfaceTxt);
    // SDL_Rect msgRect = {0, 0, 100, 100};
    
        


    
    // lua -----------------------------------------------------------------------------------------
    char buff[256];
    int err;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);          // opens Lua 
    luaopen_base(L);           // opens the basic library
    luaopen_table(L);          // opens the table library 
    luaopen_io(L);             // opens the I/O library 
    luaopen_string(L);         // opens the string lib. 
    luaopen_math(L);           // opens the math lib. 

    lPutRenderer(L, renderer);
    lPutFont(L, font);
    register_callbacks(L);
    luaL_dofile(L, "lua/display.lua");            
    
    printf("Local Distributed Processing Unit Simulator\n\n");
    
    while (true) {
        printf(">>  ");
        char *eof = fgets(buff, sizeof(buff), stdin);
        
        if (eof == NULL) break;

        // directives.
        if (strncmp(buff, "quit", 4) == 0) {
            break;
        }
        
        if (strncmp(buff, "reload", 6) == 0) { 
            luaL_dofile(L, "lua/cell.lua");
            luaL_dofile(L, "lua/display.lua");            
            luaL_dofile(L, "lua/grid.lua");
            luaL_dofile(L, "lua/instructions.lua");
            continue;
        }
        
        if (strncmp(buff, "help", 4) == 0 || strncmp(buff, "h\n", 2) == 0) {
            luaL_dofile(L, "lua/help.lua");            
            continue;
        }
        
        err = luaL_loadbuffer(L, buff, strlen(buff), "line") || lua_pcall(L, 0, 0, 0);        
        if (err) {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            perr(lua_tostring(L, -1));
            lua_pop(L, 1);  /* pop error message from the stack */
        }
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())
    // Close and destroy the window
    
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    reportUnwind();
    lua_close(L);
    return 0;
}



// static int l_square (lua_State *L) {
//     double d = lua_tonumber(L, 1);  /* get argument */
//     lua_pushnumber(L, d*d);  /* push result */
//     return 1;  /* number of results */
// }
