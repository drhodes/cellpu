
#include "grid-edit.hh"
#include "visit.hh"

class EntityRegisterVisitor : public BaseVisitor {
 private:
  EntityStore &m_es;

 public:
  EntityRegisterVisitor(EntityStore &es) {
    SDL_Event m_es = es;
  }

  void
  visit(GridEditor &ge) {
  }

  void
  visit(StatusText &status) {
  }
};
