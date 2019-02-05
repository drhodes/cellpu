#include <experimental/optional>
#include <map>
#include <memory>

#include "entity.hh"

using namespace std;
using namespace std::experimental;

class Layer {
  map<int, shared_ptr<IEntity>> m_idToEntity;
  void addEntity(shared_ptr<IEntity>);
};

class EntityStore {
  // this has a spatial hash from (xPx, yPx) -> entity-id (not yet, linear
  // search sufficient)

 private:
  map<int, shared_ptr<Layer>> m_zIndexToLayer;

  optional<shared_ptr<Layer>> getLayer(int zIndex);
  void addEntity(shared_ptr<IEntity>);
  optional<shared_ptr<IEntity>> topEntity(int, int);
};
