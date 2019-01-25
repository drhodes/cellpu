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
  Atlas m_atlas = Atlas("./media/FIXED_V0.TTF", 8);
  vector<std::shared_ptr<Cell>> m_cellVector;

 public:
  InstructionSelector();

  void accept(std::shared_ptr<Visitor> v);
  void render(SDL_Renderer *renderer);
};
