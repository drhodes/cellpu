#include <SDL2/SDL.h>
#include "visit.hh"
#include "grid-edit.hh"

class MouseMotionEventVisitor : public BaseVisitor 
{
private:
  SDL_Event m_event;
  bool m_bubble = true; // bubble events down through the z-index
                        // layers.
public:  
  EventVisitor(SDL_Event &ev) {
    SDL_Event m_event = ev;
  }
  
  void visit(GridEditor &ge) {
    if (m_bubble) {
      ge.updateFocus(ev);
      if (!ge.hasFocus()) return;
      updateOverCell(ev);
    }
  }

  void visit(StatusText &status) {
    if (m_bubble) {
      status.setRow(0, "Handling SDL_MOUSEMOTION");
    }
  }

  void visit(Cell &cell) {
    // this is for each visible cell, not every cell.
    if (cell.contains(ev)) {
      cell.showDetails();
    }
  }
  
};
