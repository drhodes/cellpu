#pragma once

#include "bbox.hh"
#include "entity-visitor.hh"
#include "visit.hh"

typedef int EntityId;

class IEntity {
 private:
  // manage a monotonic id across all entities.
  static int nextID() {
    static int id = 0;
    return id++;
  }

  const int m_id;

 protected:
  BBox m_bbox;
  bool m_hidden;

 public:
  IEntity() : m_id(nextID()) {}

  int zIndex() { return parent().zIndex() + 1; }
  int endityId() { return m_id; }

  virtual bool hasFocus() = 0;
  virtual IEntity &parent() = 0;
  virtual void hidden(bool) = 0;
  virtual bool hidden() = 0;
  virtual BBox &bbox() = 0;
};
