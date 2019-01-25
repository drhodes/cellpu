#pragma once

#include <memory>

#include "atlas.hh"
#include "display.hh"
#include "grid-edit.hh"
#include "grid.hh"
#include "instruction-selector.hh"
#include "lua.hh"
#include "term.hh"

using namespace std;

class App {
  Display dsys;
  GridEditor m_ge;
  Term m_term = Term(5, 750, 80, 17);
  InstructionSelector m_instSel;

  bool m_running = true;

 public:
  App();
  ~App() = default;

  void resizeGrid(int n);
  void eventLoop();
  void accept(std::shared_ptr<Visitor>);
  void quit();
};
