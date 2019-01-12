#pragma once

#include "grid.hh"
#include "text-box.hh"
#include "cell.hh"
#include "event-handler.hh"

class GridEditor : public EventHandler {
public:
  Grid& m_grid = *new Grid(12);
  TextBox& m_statusText = *new TextBox(*new Atlas("./media/Terminus.ttf", 16), 0, m_grid.bottom(), 80, 1);

  shared_ptr<Cell> m_overCell;
  shared_ptr<Cell> m_selectedCell;
  bool m_hasFocus;

  GridEditor();
  ~GridEditor();

  // void processEvent(SDL_Event&);
  void updateOverCell(SDL_Event &ev);
  void updateSelectedCell(SDL_Event &ev);
  void updateFocus(SDL_Event &ev);
  void handleTextInput(SDL_Event &ev);
  void showArguments();
  void setupEvents();
  void render();
  
  // these may be used to display help for user.
  void showKeys();
  void hideKeys();
};


