#pragma once
#include <memory>

// avoid cyclic includes.
class GridEditor;
class Grid;
class Term;
class App;
class InstructionSelector;

class Visitor {
public:
  virtual void visit(GridEditor&) = 0;
  virtual void visit(Grid&) = 0;
  virtual void visit(Term&) = 0;
  virtual void visit(App&) = 0;
  virtual void visit(InstructionSelector&) = 0;
};


class Visitable {
public:
  virtual void accept(std::shared_ptr<Visitor>) = 0;
  virtual ~Visitable() {}
};

// TODO. according to experts using stubs shouldn't work 
// hmm. 
class BaseVisitor :
  public Visitor
{
  void visit(Grid&) { }
  void visit(GridEditor&) { } 
  void visit(Term&) { }
  void visit(App&) { }
  void visit(InstructionSelector&) { }
};

