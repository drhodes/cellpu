#pragma once

#include "bbox.hh"

class IEntity {
 protected:
  BBox m_bbox;
  bool m_hidden;

 public:
  virtual bool hasFocus() = 0;
  virtual IEntity &parent() = 0;
  virtual void hidden(bool) = 0;
  virtual bool hidden() = 0;
  virtual BBox &bbox() = 0;

  int zIndex() { return parent().zIndex() + 1; }
};
