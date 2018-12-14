// @file
// @brief This file is marvelous.

#ifndef CALLBACKS_H
#define CALLBACKS_H

// C callbacks for lua -----------------------------------------------------------------------------
#include <lua5.3/lua.h>

namespace callback {
    int lClear(lua_State *L);
    int lSetColor(lua_State *L);
    int lDrawBox(lua_State *L);
    int lDrawText(lua_State *L);
    int lUpdate(lua_State *L);
    int lSelectCell(lua_State *L);
    int lDump(lua_State *L);

  //void register_all(lua_State *L);
}

#endif // CALLBACKS_H
