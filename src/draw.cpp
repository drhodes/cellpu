#include "draw.hh"
#include "err.hh"
#include <string>
#include <exception>

using namespace std;
#define ethrow(e, msg) throw runtime_error(string(e.what()) + string(msg) + " " + string(__FILE__));

namespace draw {
  void
  borderBox(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color border, SDL_Color fill) {
    SDL_Rect rect = {x, y, h, w};
    SDL_SetRenderDrawColor(renderer, border.r, border.g, border.b, border.a);
    SDL_RenderFillRect(renderer, &rect);
    rect.x += 2; // shrink the rect and redraw
    rect.y += 2; // to make border of width 2
    rect.h -= 2;
    rect.w -= 2; 
    SDL_SetRenderDrawColor(renderer, fill.r, fill.g, fill.b, fill.a);
    SDL_RenderFillRect(renderer, &rect);
  }

  
  void
  text(SDL_Renderer *renderer, Atlas &atlas, int x, int y, std::string txt) {
    SDL_Rect msgRect = { x, y, atlas.surfWidth_, atlas.surfHeight_ };  
    for (int i=0; txt[i]; i++) {
      try {
        SDL_Texture* glyph = atlas.getGlyph(txt[i]);
        SDL_RenderCopy(renderer, glyph, nullptr, &msgRect);
        msgRect.x += atlas.surfWidth_;
      } catch(exception e) {
        ethrow(e, "failed to get a glyph in draw::text");
          //throw runtime_error(string(e.what()) + string("\n failed to get a glyph in termRender"));
      }
    }
  }
}
