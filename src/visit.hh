#pragma once

class GridEditor;

class Visitor {
public:
  virtual void visit(GridEditor&) = 0;
  //~Visitor() = default;  
};

class Visitable {
public:
  virtual void accept(Visitor&) = 0;
};


