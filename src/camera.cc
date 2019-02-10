#include "camera.hh"

Camera::Camera() {
  updateBBox();
}

void
Camera::updateBBox() {
  int x, y;
  display::getWindowSize(&x, &y);
  m_bbox.updateSize(x, y);
}

void
Camera::panEast() {
  cout << "[STUB] panning East" << endl;
}

void
Camera::panWest() {
  cout << "[STUB] panning West" << endl;
}

void
Camera::panNorth() {
  cout << "[STUB] panning North" << endl;
}

void
Camera::panSouth() {
  cout << "[STUB] panning South" << endl;
}
