#pragma once
#include <memory>

class GridEditor;

class Visitor {
public:
  virtual void visit(GridEditor&) = 0;
  //~Visitor() = default;  
};

class Visitable {
public:
  virtual void accept(std::shared_ptr<Visitor>) = 0;
};


