#include "visit.hh"
#include "grid-edit.hh"
  
class PanGridVisitor : public BaseVisitor 
{  
private:
  int m_direction;
public:  
  const int NORTH = 0;
  const int EAST = 1;
  const int SOUTH = 2;
  const int WEST = 3;
  
  PanGridVisitor(int direction) {
    m_direction = direction;
  }  
  void visit(GridEditor &ge) {
    switch (m_direction) {
    case NORTH:
      ge.panNorth();
      return;
    case EAST:
      ge.panEast();
      return;
    case SOUTH:
      ge.panSouth();
      return;
    case WEST:
      ge.panWest();
      return;
    }
  }
};
