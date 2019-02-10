// camera object lives over the cell grid.

// the cell universe starts at 0,0 upper left, there are no negative
// values for cell locations.

#include "bbox.hh"
#include "display.hh"

class Camera {
 private:
  int m_x = 0;
  int m_y = 0;
  BBox m_bbox;  // this is the size of the view port in pixels.

 public:
  Camera();

  void panEast();
  void panWest();
  void panNorth();
  void panSouth();
  void updateBBox();
};
