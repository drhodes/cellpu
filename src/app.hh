#pragma once

#include <memory>

#include "term.hh"
#include "grid.hh"
#include "grid-edit.hh"
#include "atlas.hh"
#include "lua.hh"
#include "display.hh"

using namespace std;

class App {  
  Display dsys;
  GridEditor &m_ge = *new GridEditor();
  Term &m_term = *new Term(5, 750, 80, 17);  

public:
  App();
  ~App();

  void resizeGrid(int n);
  void eventLoop();
  void accept(std::shared_ptr<Visitor>);
};
