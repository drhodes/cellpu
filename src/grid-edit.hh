#pragma once

#include "cell.hh"
#include "entity.hh"
#include "grid.hh"
#include "text-box.hh"
#include "visit.hh"

class GridEditor : public Visitable, public IEntity {
  Atlas m_atlas{"./media/Terminus.ttf", 16};

 public:
  Grid m_grid{*this, 12};
  TextBox m_statusText = TextBox(m_atlas, 0, m_grid.bottom(), 80, 1);
  shared_ptr<Cell> m_overCell;
  bool m_hasFocus;
  IEntity &m_parent;

  GridEditor() = delete;
  GridEditor(IEntity &);

  void updateOverCell(SDL_Event &ev);
  void updateFocus(SDL_Event &ev);
  void handleTextInput(SDL_Event &ev);
  void showArguments();
  void setupEvents();
  void render();
  void accept(shared_ptr<Visitor>);
  void setSelectAllCells(bool);
  void setSelectedCellsInstruction(shared_ptr<Instruction> inst);
  void toggleSelectCurCell(SDL_Event &ev);

  void statusText(string);

  void panEast();
  void panWest();
  void panNorth();
  void panSouth();

  void zoomIn();
  void zoomOut();

  // entity
  bool hasFocus();
  IEntity &parent();
  void hidden(bool);
  bool hidden();
  BBox &bbox();
};
