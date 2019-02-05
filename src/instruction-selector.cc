#include "instruction-selector.hh"
#include "display.hh"

InstructionSelector::InstructionSelector() {
  m_cellVector.push_back(make_shared<Cell>(0, 0));
  m_cellVector[0]->setInstruction(make_shared<NOOP>());
  ;

  m_cellVector.push_back(make_shared<Cell>(1, 0));
  m_cellVector[1]->setInstruction(make_shared<AND>());
}

// InstructionSelector::
void InstructionSelector::accept(std::shared_ptr<Visitor> v) {
  v->visit(*this);
}

void InstructionSelector::renderBackground(SDL_Renderer *renderer) {
  // render a large translucent square to indicate sole focus on this element.
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x77);
  SDL_Rect rect = {0, 0, 10000, 10000};
  SDL_RenderFillRect(renderer, &rect);
}

void InstructionSelector::render(SDL_Renderer *renderer) {
  if (show()) {
    renderBackground(renderer);
  }
}
