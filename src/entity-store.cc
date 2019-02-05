#include "entity-store.hh"
#include <experimental/optional>

void
Layer::addEntity(shared_ptr<IEntity> ent) {
}

optional<shared_ptr<Layer>>
EntityStore::getLayer(int zIndex) {
  return nullopt;
}

void
EntityStore::addEntity(shared_ptr<IEntity> ent) {
}

optional<shared_ptr<IEntity>>
EntityStore::topEntity(int xPx, int yPx) {
  // find objects containing x, y.
  // pick the one which is not hidden and has highest z-index.
  return nullopt;
}
