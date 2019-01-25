#pragma once

#include "grid.hh"
#include "text-box.hh"
#include "cell.hh"
#include "event-handler.hh"
#include "visit.hh"

class GridEditor :
  public Visitable
{
public:
  Grid& m_grid = *new Grid(12);
  TextBox& m_statusText = *new TextBox(*new Atlas("./media/Terminus.ttf", 16), 0, m_grid.bottom(), 80, 1);

  shared_ptr<Cell> m_overCell;
  bool m_hasFocus;

  GridEditor();
  ~GridEditor();
  
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
  bool hasFocus();

  void panEast();
  void panWest();
  void panNorth();
  void panSouth();

  void zoomIn();
  void zoomOut();

  
  // these may be used to display help for user.
  void showKeys();
  void hideKeys();
};

