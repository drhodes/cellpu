#include "display.hh"
#include "err.hh"


namespace display {
  SDL_Window *_window = NULL;
  SDL_Renderer *_renderer = NULL;

  SDL_Window *getWindow() { return _window; }
  SDL_Renderer *getRenderer() { return _renderer; }
}

Display::Display() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_StartTextInput();
  
  display::_window =
    SDL_CreateWindow ( "proc sim",                // window title
                       SDL_WINDOWPOS_UNDEFINED,   // initial x position
                       SDL_WINDOWPOS_UNDEFINED,   // initial y position
                       1150,                      // width, in pixels                               
                       1150,                      // height, in pixels
                       SDL_WINDOW_OPENGL
                       );
  
  display::_renderer = SDL_CreateRenderer(display::getWindow(), -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(display::getRenderer(), SDL_BLENDMODE_BLEND);
  TTF_Init();


  
  // Check that the window was successfully created
  if (display::getWindow() == NULL) {
    // In the case that the window could not be made...
    perr("Could not create window"); perr(SDL_GetError());
    return;
  }
}

Display::~Display() {
  SDL_DestroyWindow(display::getWindow());
  SDL_DestroyRenderer(display::getRenderer());
  SDL_Quit();
  TTF_Quit();
}
