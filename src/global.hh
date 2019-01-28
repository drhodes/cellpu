#pragma once

#include <memory>

#include "cmdr.hh"
#include "lua.hh"

namespace global {
Cmdr &cmdr();
LuaMgr &lman();
void cleanup();
}  // namespace global
