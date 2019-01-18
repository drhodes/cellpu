#pragma once
#include <memory>

// avoid cyclic includes.
class GridEditor;
class Grid;
class Cell;
class Term;


class Visitor {
public:
  virtual void visit(GridEditor&) = 0;
  virtual void visit(Grid&) = 0;
  virtual void visit(Cell&) = 0;
  virtual void visit(Term&) = 0;
};


class Visitable {
public:
  virtual void accept(std::shared_ptr<Visitor>) = 0;
};

// TODO. according to experts using stubs shouldn't work 
// hmm. 
class BaseVisitor :
  public Visitor
{
  void visit(Grid &g) { }
  void visit(GridEditor &ge) { } 
  void visit(Cell &cell) { }
  void visit(Term &term) { }
};

