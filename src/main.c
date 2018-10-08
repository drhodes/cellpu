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
#include "display-state.h"
#include "callbacks.h"
#include "term.h"

// Register callbacks ------------------------------------------------------------------------------

void doFile(lua_State *L, const char *filename) {
    int err = luaL_dofile(L, filename);
    if (err) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        perr(lua_tostring(L, -1));
        lua_pop(L, 1);  /* pop error message from the stack */
    }
}

int main (void) {
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

    // SDL -----------------------------------------------------------------------------------------
    
    SDL_Init(SDL_INIT_VIDEO);            
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    window = SDL_CreateWindow( "proc sim",                // window title
                               SDL_WINDOWPOS_UNDEFINED,   // initial x position
                               SDL_WINDOWPOS_UNDEFINED,   // initial y position
                               1100,                      // width, in pixels
                               1100,                      // height, in pixels
                               SDL_WINDOW_OPENGL          // flags - see below
                               );
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    lPutRenderer(L, renderer);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        perr("Could not create window"); perr(SDL_GetError());
        return 1;
    }

    // font ----------------------------------------------------------------------------------------
    
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("./media/FIXED_V0.TTF", 8);
    lPutFont(L, font);
    
    register_callbacks(L);
    
    doFile(L, "lua/display.lua");            
    doFile(L, "lua/cell.lua");
    doFile(L, "lua/grid.lua");
    doFile(L, "lua/instructions.lua");
    //doFile(L, "lua/startup.lua");
    
    printf("Local Distributed Processing Unit Simulator\n\n");

    // terminal ------------------------------------------------------------------------------------
    Term* term = newTerm(window, 80);
    termPut(term, "top");
    termPut(term, "line1");
    termPut(term, "line2");
    termPut(term, "bottom");
    
    while (true) {
        //SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        printf(">>  ");

        char *eof = fgets(buff, sizeof(buff), stdin);
        
        if (eof == NULL) break;

        // directives.
        if (strncmp(buff, "quit", 4) == 0) {
            break;
        }
        
        if (strncmp(buff, "reload", 6) == 0) { 
            doFile(L, "lua/cell.lua");
            doFile(L, "lua/display.lua");            
            doFile(L, "lua/grid.lua");
            doFile(L, "lua/instructions.lua");
            doFile(L, "lua/startup.lua");
            continue;
        }
        
        if (strncmp(buff, "help", 4) == 0 || strncmp(buff, "h\n", 2) == 0) {
            doFile(L, "lua/help.lua");            
            continue;
        }
        
        err = luaL_loadbuffer(L, buff, strlen(buff), "line") || lua_pcall(L, 0, 0, 0);        
        if (err) {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            perr(lua_tostring(L, -1));
            lua_pop(L, 1);
        }
        
        termRender(term, renderer);
        SDL_RenderPresent(renderer);
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())
    // Close and destroy the window
    
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    
    // Clean up
    SDL_Quit();
    TTF_Quit();
    dumpStack();
    lua_close(L);
    return 0;
}


// static int l_square (lua_State *L) {
//     double d = lua_tonumber(L, 1);  /* get argument */
//     lua_pushnumber(L, d*d);  /* push result */
//     return 1;  /* number of results */
// }
