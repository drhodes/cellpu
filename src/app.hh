#pragma once

#include <memory>

#include "atlas.hh"
#include "bbox.hh"
#include "cmdr.hh"
#include "display.hh"
#include "entity.hh"
#include "grid-edit.hh"
#include "grid.hh"
#include "instruction-selector.hh"
#include "lua.hh"
#include "term.hh"

using namespace std;

class App : IEntity {
 private:
  Display dsys;
  GridEditor m_ge;
  Term m_term = Term(*this, 5, 750, 80, 17);
  InstructionSelector m_instSel;
  bool m_running = true;

 public:
  App();
  App(const App &) = delete;

  void resizeGrid(int n);
  void eventLoop();
  void accept(std::shared_ptr<Visitor>);
  void quit();

  // IEntity.
  bool hasFocus();
  IEntity &parent();
  BBox &bbox();
  int zIndex();
  void hidden(bool);
  bool hidden();
};
