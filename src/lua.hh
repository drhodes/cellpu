#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class Grid;


class LuaMgr {
private:
  lua_State *_LS = nullptr;

public:  
  LuaMgr();
  ~LuaMgr();
  
  void doFile(const char *filename);
  void doLine(std::string);

  
  void putRenderer(SDL_Renderer*);
  SDL_Renderer* getRenderer();
  
  void putFont(TTF_Font *font);
  TTF_Font* getFont();
  
  void putGrid(Grid *grid);
  const Grid& getGrid();

  void register_callbacks();
};
