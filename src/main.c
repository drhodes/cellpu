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

// Register callbacks -----------------------------------------------------------------------------
lua_State *L = 0; //luaL_newstate();



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
    
    L = luaL_newstate();
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
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //SDL_RENDERER_PRESENTVSYNC );
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
    
    printf("Local Distributed Processing Unit Simulator\n\n");

    // terminal ------------------------------------------------------------------------------------
    Atlas* atlas = newAtlas(renderer);    
    Term* term = newTerm(window, atlas, 5, 650, 80, 17);
    nullDie(term);
    
    termPut(term, "Distributed Processing Unit Simulator");
    termPut(term, "--");
    termPut(term, "2");
    termPut(term, "3");
    termPut(term, "4");
    termPut(term, "5");
    termPut(term, "6");
    
    SDL_Event event;
    while( true ) {
        Uint64 loopTimeStart = SDL_GetTicks();
        
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {            
                if(event.key.keysym.scancode == SDL_SCANCODE_Q) {
                    exit(0);
                }
            }
            // different state machines for different parts of the app.
            // the terminal should own one?
            // each cell could own a state machine.
            // ok, event listen interface for each
            // guiProcessEvent(gui, &event);
        
            termProcessEvent(term, &event);
        }        
        termRender(term, renderer);
        SDL_RenderPresent(renderer);
        Uint64 loopTimeStop = SDL_GetTicks();
        Uint64 delta = loopTimeStop - loopTimeStart;
        //double ddelta = ((double)delta*1000) / (double)SDL_GetPerformanceFrequency();
        int wait = delta > 16 ? 0 : 16 - delta;
        SDL_Delay(wait);
    }    
    printf("SDL: %s\n", SDL_GetError());
    
    // Clean up    

    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    freeTerm(term);
    freeAtlas(atlas);
    
    SDL_Quit();
    TTF_Quit();
    dumpStack();
    // lua_close(L);
    return 0;
}
