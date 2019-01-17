#include <queue>
#include <optional>

#include "cmdr.hh"

using namespace std;

void
Cmdr::pushCmd(shared_ptr<Cmd> cmd) {
  m_commands.push(cmd);
}

void
Cmdr::pushVisitor(shared_ptr<Visitor> v) {
  m_visitors.push(v);
}


optional<shared_ptr<Cmd>>
Cmdr::frontCmd() {
  
  if (m_commands.size() == 0) {
    return nullopt;
  } else {
    auto e = m_commands.front();
    m_commands.pop();
    return make_optional(e);
  }
}

std::optional<shared_ptr<Visitor>>
Cmdr::frontVisitor() {
  if (m_visitors.size() == 0) {
    return nullopt;
  } else {
    auto e = m_visitors.front();
    m_visitors.pop();
    return make_optional(e);
  }
}
