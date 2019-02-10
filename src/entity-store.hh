#include <experimental/optional>
#include <map>
#include <memory>

#include "entity.hh"

using namespace std;
using namespace std::experimental;

class Layer {
  // this has a spatial hash from (xPx, yPx) -> entity-id (not yet, linear
  // search sufficient)
  map<int, shared_ptr<IEntity>> m_idToEntity;
  void addEntity(shared_ptr<IEntity>);
};

class EntityStore {
  map<int, shared_ptr<Layer>> m_zIndexToLayer;

 private:
  optional<shared_ptr<Layer>> getLayer(int zIndex);
  void addEntity(shared_ptr<IEntity>);
  optional<shared_ptr<IEntity>> topEntity(int, int);
};
