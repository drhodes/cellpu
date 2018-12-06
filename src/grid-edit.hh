#pragma once

#include "grid.hh"
#include "cell.hh"

class GridEditor {
public:
  Grid &m_grid;
  shared_ptr<Cell> m_overCell;
  shared_ptr<Cell> m_selectedCell;
  bool m_hasFocus;

  GridEditor(Grid&);
  ~GridEditor();

  void processEvent(SDL_Event&);
  void updateOverCell(SDL_Event &ev);
  void updateSelectedCell(SDL_Event &ev);
  void updateFocus(SDL_Event &ev);
  void handleTextInput(SDL_Event &ev);
  void showArguments();

  // these may be used to display help for user.
  void showKeys();
  void hideKeys();
};


