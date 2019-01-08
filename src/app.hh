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

  Grid &m_grid;
  GridEditor &m_ge;
    
  Term &m_term = *new Term(5, 750, 80, 17);  

public:
  App();
  ~App();
  
  void eventLoop();
};
