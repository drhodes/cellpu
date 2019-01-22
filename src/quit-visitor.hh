#pragma once

#include "visit.hh"
#include "app.hh"
  
class QuitVisitor : public BaseVisitor 
{
public:  
  QuitVisitor() { }
  
  void visit(App &app) {
    app.quit();
  }
};
