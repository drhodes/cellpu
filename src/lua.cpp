#include <string>

//c#include "callbacks.hh"
#include "lua.hh"
#include "err.hh"
#include "callbacks.hh"

LuaMgr::LuaMgr() {
  // init global state.
  _LS = luaL_newstate();
  nullDie(_LS);
  
  luaL_openlibs(_LS);          // opens Lua 
  luaopen_base(_LS);           // opens the basic library
  luaopen_table(_LS);          // opens the table library 
  luaopen_io(_LS);             // opens the I/O library 
  luaopen_string(_LS);         // opens the string lib. 
  luaopen_math(_LS);           // opens the math lib. 
}

LuaMgr::~LuaMgr() {
  lua_close(_LS);
}

void
LuaMgr::doFile(const char *filename) {  
  int err = luaL_dofile(_LS, filename);
  if (err) {
    fprintf(stderr, "%s\n", lua_tostring(_LS, -1));
    perr(lua_tostring(_LS, -1));
    lua_pop(_LS, 1);  // pop error message from the stack 
  }
}

void
LuaMgr::doLine(std::string line) {
  int err = luaL_loadbuffer(_LS, line.c_str(), line.length(), "line") || lua_pcall(_LS, 0, 0, 0);
  
  if (err) {
    string errStr(lua_tostring(_LS, -1));
    fprintf(stderr, "%s\n", lua_tostring(_LS, -1));
    perr(errStr);
    lua_pop(_LS, 1);
  }
}


void
LuaMgr::putRenderer(SDL_Renderer *renderer) {
    lua_pushinteger(_LS, (uintptr_t)renderer);
    lua_setglobal(_LS, "renderer");
}

SDL_Renderer*
LuaMgr::getRenderer() {
    // fetch the pointer to renderer and place at top of stack.
    lua_getglobal(_LS, "renderer");
    // get top of stack and coerce to pointer type.
    uintptr_t ptr2 = (uintptr_t)lua_tointeger(_LS, -1);
    lua_pop(_LS, 1);
    return (SDL_Renderer*)ptr2;
}

// managing the SDL font state in lua. ---------------------------------------------------------

void
LuaMgr::putFont(TTF_Font *font)
{
    lua_pushinteger(_LS, (uintptr_t)font);
    lua_setglobal(_LS, "font");
}

TTF_Font*
LuaMgr::getFont() {
    // fetch the pointer to font and place at top of stack.
    lua_getglobal(_LS, "font");
    // get top of stack and coerce to pointer type.
    uintptr_t ptr2 = (uintptr_t)lua_tointeger(_LS, -1);
    lua_pop(_LS, 1);
    return (TTF_Font*)ptr2;
}

// managing the grid -------------------------------------------------------------------------------

void
LuaMgr::putGrid(Grid *grid) {
  lua_pushinteger(_LS, (uintptr_t)grid);
    lua_setglobal(_LS, "grid");
}

const Grid&
LuaMgr::getGrid() {
  // fetch the pointer to grid and place at top of stack.
  lua_getglobal(_LS, "grid"); 
  
  // get top of stack and coerce to pointer type.    
  uintptr_t *ptr2 = new uintptr_t;
  *ptr2 = (uintptr_t)lua_tointeger(_LS, -1);
  lua_pop(_LS, 1);
  return reinterpret_cast<const Grid&>(*ptr2);
}

void
LuaMgr::register_callbacks() {
  // clear the renderer
  lua_pushcfunction(_LS, callback::lClear);
  lua_setglobal(_LS, "clear");

  lua_pushcfunction(_LS, callback::lSetColor);
  lua_setglobal(_LS, "setColor");

  lua_pushcfunction(_LS, callback::lDrawBox);
  lua_setglobal(_LS, "drawBox");

  lua_pushcfunction(_LS, callback::lUpdate);
  lua_setglobal(_LS, "update");
    
  lua_pushcfunction(_LS, callback::lSelectCell);
  lua_setglobal(_LS, "selectCell");

  lua_pushcfunction(_LS, callback::lDump);
  lua_setglobal(_LS, "dump");
  
  lua_pop(_LS, 6);
}
