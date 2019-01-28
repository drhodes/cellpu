#include <memory>

#include "global.hh"

namespace global {
Cmdr m_cmdr;
LuaMgr m_lman;

Cmdr &cmdr() { return m_cmdr; }
LuaMgr &lman() { return m_lman; }

void cleanup() {
  delete &m_cmdr;
  delete &m_lman;
}
}  // namespace global
