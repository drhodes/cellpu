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

  Atlas &m_gridAtlas;
  Grid &m_grid;
  GridEditor& m_ge;
    
  Atlas& m_termAtlas;
  Term& m_term;

public:
  App();
  void eventLoop();
};
