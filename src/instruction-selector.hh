#pragma once

#include <memory>

#include "cell.hh"
#include "display.hh"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

// a popup with all the possible instructions
class InstructionSelector : public Visitable {
 private:
  Atlas m_atlas{"./media/FIXED_V0.TTF", 8};
  vector<std::shared_ptr<Cell>> m_cellVector;
  bool m_focus = false;
  bool m_show = false;

  void renderBackground(SDL_Renderer *renderer);

 public:
  InstructionSelector();

  void
  focus(bool b) {
    m_focus = b;
  }
  bool
  focus() {
    return m_focus;
  }

  void
  show(bool b) {
    m_show = b;
  }
  bool
  show() {
    return m_show;
  }

  void accept(std::shared_ptr<Visitor> v);
  void render(SDL_Renderer *renderer);
};
