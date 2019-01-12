#pragma once

#include <queue>
#include <optional>

class Cmd {
  
};

// singleton.
class Cmdr {
private:
  std::queue<Cmd> m_commands;
  
public:
  void pushCmd(Cmd &cmd);
  std::optional<Cmd> frontCmd();
};



