#include "visit.hh"
#include "grid-edit.hh"

class SelectCellVisitor :
  public Visitor
{
private:
  int m_x, m_y;
public:  
  SelectCellVisitor(int x, int y) {
    m_x = x;
    m_y = y;
  }  
  void visit(GridEditor &ge) {    
    //ge.m_grid.selectCell(m_x, m_y);
  }
  void visit(Grid &g) {
    g.selectCell(m_x, m_y);
  }
  void visit(Cell &cell) {
    //cell.setSelect(true))
  }  
};
