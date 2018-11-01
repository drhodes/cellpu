#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>

#include <assert.h>
#include <stdbool.h> 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err.h"
#include "display-state.h"
#include "callbacks.h"
#include "term.h"
#include "grid.h"
#include "instruction.h"
#include "opcode.h"
#include "grid-edit.h"

lua_State *L = NULL; 

void doFile(const char *filename) {
    int err = luaL_dofile(L, filename);
    if (err) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        perr(lua_tostring(L, -1));
        lua_pop(L, 1);  // pop error message from the stack 
    }
}

void initLua() {
    // init global state.
    L = luaL_newstate();
    nullDie(L);
    luaL_openlibs(L);          // opens Lua 
    luaopen_base(L);           // opens the basic library
    luaopen_table(L);          // opens the table library 
    luaopen_io(L);             // opens the I/O library 
    luaopen_string(L);         // opens the string lib. 
    luaopen_math(L);           // opens the math lib. 
}

int main (void) {
    initLua();
    
    // SDL -----------------------------------------------------------------------------------------
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_StartTextInput();
    
    window = SDL_CreateWindow( "proc sim",                // window title
                               SDL_WINDOWPOS_UNDEFINED,   // initial x position
                               SDL_WINDOWPOS_UNDEFINED,   // initial y position
                               1150,                      // width, in pixels                               
                               1150,                      // height, in pixels
                               SDL_WINDOW_OPENGL
                               );
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //SDL_RENDERER_PRESENTVSYNC );
    lPutRenderer(L, renderer);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // SDL_EnableKeyRepeat(0, 0); // disable key repeat.
 

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        perr("Could not create window"); perr(SDL_GetError());
        return 1;
    }

    // Opcode opc = NOP;
    // opcodeToJson(opc);

    // move this to test code.
    Opcode opc = jsonToOpcode("{\"type\": \"Opcode\", \"value\": 0}");
    printf("opcode :%d\n", opc);
    
    // font ----------------------------------------------------------------------------------------
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("./media/FIXED_V0.TTF", 8);
    lPutFont(L, font);
    
    register_callbacks(L);

    // grid ----------------------------------------------------------------------------------------
    Atlas *gridAtlas = newAtlas(renderer, "./media/FIXED_V0.TTF", 8);
    Grid *grid = newGrid(100, 12, gridAtlas);
    lPutGrid(L, grid);

    GridEditor *ge = newGridEditor(grid);
    
    
    // terminal ------------------------------------------------------------------------------------
    Atlas *termAtlas = newAtlas(renderer, "./media/Terminus.ttf", 16);
    Term *term = newTerm(window, termAtlas, 5, 750, 80, 17);
    nullDie(term);

    termPut(term, "-- PUNC   Distributed Processing Unit Simulator, the repl is Lua.");
    termPut(term, "--  UNCPU -------------------------------------------------------");
    
    SDL_Event event;
    while( true ) {
        Uint64 loopTimeStart = SDL_GetTicks();
        
        while(SDL_PollEvent(&event)) {
            
            // different state machines for different parts of the app.
            // the terminal should own one?
            // each cell could own a state machine.
        
            gridEditorProcessEvent(ge, &event);
            termProcessEvent(term, &event);
            gridProcessEvent(grid, &event);
            
            if (event.type == SDL_KEYDOWN) {            
                if(event.key.keysym.scancode == SDL_SCANCODE_Q) {
                    goto done;
                }
            }
        }        
        termRender(term, renderer);
        gridRender(grid, renderer);
        
        SDL_RenderPresent(renderer);
        Uint64 loopTimeStop = SDL_GetTicks();
        Uint64 delta = loopTimeStop - loopTimeStart;
        //double ddelta = ((double)delta*1000) / (double)SDL_GetPerformanceFrequency();
        int wait = delta > 32 ? 0 : 32 - delta;
        SDL_Delay(wait);
    }    
    printf("SDL: %s\n", SDL_GetError());
    
 done:
    freeTerm(term);
    freeAtlas(termAtlas);
    freeAtlas(gridAtlas);
    
    SDL_DestroyWindow(window);
    // TTF_CloseFont(font);
    
    SDL_Quit();
    TTF_Quit();
    dumpStack();
    lua_close(L);
    return 0;
}
