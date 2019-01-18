#include "visit.hh"
#include "grid-edit.hh"
  
class ZoomGridVisitor : public BaseVisitor 
{
private:
  int m_factor;
public:  
  ZoomGridVisitor(int factor) {
    m_factor = factor;
  }  
  void visit(Grid &g) {
    g.zoom(m_factor);
  }
  void visit(Cell &c) {
    c.setZoom(m_factor);
  }
};
