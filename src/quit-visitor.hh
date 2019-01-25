#pragma once

#include "app.hh"
#include "visit.hh"

class QuitVisitor : public BaseVisitor {
 public:
  QuitVisitor() {}

  void visit(App &app) { app.quit(); }
};
