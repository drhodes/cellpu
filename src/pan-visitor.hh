#pragma once

#include "camera.hh"
#include "visit.hh"

class PanVisitor : public BaseVisitor {
 private:
  string m_cmd;

 public:
  PanVisitor(string cmd) {
    m_cmd = cmd;
  }
  void
  visit(Camera &cam) {
    if (m_cmd == "pan-east")
      cam.panEast();
    if (m_cmd == "pan-west")
      cam.panWest();
    if (m_cmd == "pan-north")
      cam.panNorth();
    if (m_cmd == "pan-south")
      cam.panSouth();
  }
};
