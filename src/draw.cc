#include <string>
#include <exception>
#include <memory>

#include "draw.hh"
#include "err.hh"
#include "display.hh"

using namespace std;

namespace draw {
  void
  borderBox(int x, int y, int w, int h, SDL_Color border, SDL_Color fill) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(display::getRenderer(), border.r, border.g, border.b, border.a);
    SDL_RenderFillRect(display::getRenderer(), &rect);
    rect.x += 1; // shrink the rect and redraw
    rect.y += 1; // to make border of width 2
    rect.h -= 2;
    rect.w -= 2; 
    SDL_SetRenderDrawColor(display::getRenderer(), fill.r, fill.g, fill.b, fill.a);
    SDL_RenderFillRect(display::getRenderer(), &rect);
  }
  
  void
  text(Atlas& atlas, int x, int y, std::string txt) {
    SDL_Rect msgRect = { x, y, atlas.surfWidth_, atlas.surfHeight_ };  
    for (int i=0; txt[i]; i++) {
      optional<SDL_Texture*> glyph = atlas.getGlyph(txt[i]);
      if (glyph.has_value()) {
        SDL_RenderCopy(display::getRenderer(), glyph.value(), nullptr, &msgRect);
        msgRect.x += atlas.surfWidth_;
      } else {
        // todo setup loggin for warnings.
      }
    }
  }
  // namespace draw
}
