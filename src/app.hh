#pragma once

#include <memory>

#include "term.hh"
#include "grid.hh"
#include "grid-edit.hh"
#include "atlas.hh"
#include "lua.hh"
#include "display.hh"
#include "instruction-selector.hh"

using namespace std;

class App {  
  Display dsys;
  GridEditor m_ge;
  Term m_term = Term(5, 750, 80, 17);
  InstructionSelector m_instSel;  
  
  bool m_running = true;
public:
  App();
  ~App();

  void resizeGrid(int n);
  void eventLoop();
  void accept(std::shared_ptr<Visitor>);
  void quit();

};
