#pragma once

#include <queue>
#include <optional>
#include <memory>
#include "visit.hh"

using namespace std;

class Cmd {
public:
  virtual ~Cmd() = default;
};

// singleton.
class Cmdr {
private:
  std::queue<shared_ptr<Cmd>> m_commands;
  std::queue<shared_ptr<Visitor>> m_visitors;
  
public:
  void pushCmd(shared_ptr<Cmd> cmd);
  void pushVisitor(shared_ptr<Visitor>);
  std::optional<shared_ptr<Cmd>> frontCmd();
  std::optional<shared_ptr<Visitor>> frontVisitor();
};

class CmdNode {
public:
  virtual void order(shared_ptr<Cmd>) = 0;
  virtual ~CmdNode() {
  }
};


