#include "grid-edit.hh"
#include "visit.hh"

class SelectCellVisitor : public BaseVisitor {
 private:
  int m_x, m_y;

 public:
  SelectCellVisitor(int x, int y) {
    m_x = x;
    m_y = y;
  }
  void visit(Grid &g) { g.selectCell(m_x, m_y); }
};
