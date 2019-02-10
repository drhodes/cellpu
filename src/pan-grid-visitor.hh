#include "grid-edit.hh"
#include "visit.hh"

class PanCameraVisitor : public BaseVisitor {
 private:
  int m_direction;

 public:
  const int NORTH = 0;
  const int EAST = 1;
  const int SOUTH = 2;
  const int WEST = 3;

  PanCameraVisitor(int direction) {
    m_direction = direction;
  }
  void
  visit(GridEditor &ge) {
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
