#include "grid-edit.hh"
#include "visit.hh"

class ZoomGridVisitor : public BaseVisitor {
 private:
  int m_factor;

 public:
  ZoomGridVisitor(int factor) { m_factor = factor; }
  void visit(Grid &g) { g.zoom(m_factor); }
};
