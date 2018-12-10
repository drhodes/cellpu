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

#include "err.hh"
//#include "display-state.hh"
#include "callbacks.hh"
#include "term.hh"
#include "grid.hh"
#include "instruction.hh"
#include "opcode.hh"
#include "grid-edit.hh"
#include "lua.hh"


LuaMgr lman;

int main (void) {
    
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
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

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
  lman.putFont(font);
  lman.register_callbacks();

  // grid ----------------------------------------------------------------------------------------
  Atlas gridAtlas(renderer, "./media/FIXED_V0.TTF", 8);
  Grid grid(100, 12, gridAtlas);
  lman.putGrid(&grid);
  GridEditor ge(grid);
    
  // terminal ------------------------------------------------------------------------------------
  Atlas termAtlas(renderer, "./media/Terminus.ttf", 16);
  Term term(window, termAtlas, 5, 750, 80, 17);

  term.put("-- Localized Processing Unit, the repl is lua.");
    
  SDL_Event event;
  while( true ) {
    Uint64 loopTimeStart = SDL_GetTicks();
        
    while(SDL_PollEvent(&event)) {           
      // different state machines for different parts of the app.
      // the terminal should own one?
      // each cell could own a state machine.
        
      ge.processEvent(event);
      term.processEvent(&event);
      grid.processEvent(event);
            
      if (event.type == SDL_KEYDOWN) {            
        if(event.key.keysym.scancode == SDL_SCANCODE_Q) {
          goto done;
        }
      }
    }
        
    term.render(renderer);
    grid.render(renderer);
    SDL_RenderPresent(renderer);
    Uint64 loopTimeStop = SDL_GetTicks();
    Uint64 delta = loopTimeStop - loopTimeStart;
    int wait = delta > 32 ? 0 : 32 - delta;
    SDL_Delay(wait);
  }
  
  printf("SDL Error?: %s\n", SDL_GetError());
    
 done:
  
  SDL_DestroyWindow(window);
  SDL_Quit();
  TTF_Quit();
  _estack.dump();
  return 0;
}
