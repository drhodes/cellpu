#pragma once
#include <memory>

class GridEditor;
class Grid;
class Cell;

class Visitor {
public:
  virtual void visit(GridEditor&) = 0;
  virtual void visit(Grid&) = 0;
  virtual void visit(Cell&) = 0;
  //~Visitor() = default;  
};


class Visitable {
public:
  virtual void accept(std::shared_ptr<Visitor>) = 0;
};


// TODO. this is redundent and thought it shouldn't work.
class BaseVisitor :
  public Visitor
{
  void visit(Grid &g) { }
  void visit(GridEditor &ge) { } 
  void visit(Cell &cell) { }
};

