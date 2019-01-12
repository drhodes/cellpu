#include <queue>
#include <optional>

#include "cmdr.hh"

using namespace std;

void
Cmdr::pushCmd(Cmd &cmd) {
  m_commands.push(cmd);
}

optional<Cmd>
Cmdr::frontCmd() {
  
  if (m_commands.size() == 0) {
    return nullopt;
  } else {
    auto e = m_commands.front();
    m_commands.pop();
    return make_optional(e);
  }
}

