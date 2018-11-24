#include "cell.h"
#include "err.h"
#include "instruction.h"

using namespace std;

// struct Cell; //fwd decl

// typedef struct {
//     int x, y, value, size;
//     bool selected, broadcasting, listening;
//     int dataReg, colReg, rowReg;
//     int op; // this will be of type Instruction soon.
// } Cell;


Cell::Cell(int x, int y) {
  this->x = x;
  this->y = y;
  size = 60;
  selected = false;
  broadcasting = false;
  listening = false;
  inst = iNOP();
  rowReg = 0;
  colReg = 0;
  dataReg = 0;
  value = 0;
}

void
Cell::setSelect(bool b) {
  selected = b;
  //printf("cell->selected: %d\n", cell->selected);
}

SDL_Color
Cell::color() {
  // change this.
  SDL_Color c = {0x56, 0x56, 0x56, 0xFF};
  return c;
}

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
drawText(SDL_Renderer *renderer, Atlas *atlas, int x, int y, string txt) {
  SDL_Rect msgRect = { x, y, atlas->surfWidth, atlas->surfHeight };

  for (int i=0; txt[i]; i++) {
    SDL_Texture* glyph = atlasGetGlyph(atlas, txt[i]);
    nullDieMsg(glyph, "failed to get a glyph in termRender");            
    SDL_RenderCopy(renderer, glyph, NULL, &msgRect);
    msgRect.x += atlas->surfWidth;
  }
}

void
Cell::cycle(struct Grid *grid) {
  // the instruction needs to see the neighborhood, so it needs a
  // pointer to grid. 
  // inst->op(grid, cell);
}

string
Cell::instructionName() {
  return inst->name;
}

void
Cell::render(Atlas *atlas, SDL_Renderer *renderer) {
  int sz = this->size;
  int n = 0;

  SDL_Color cellBorderColor = {0x00, 0x00, 0x00, 0xFF};

  // background box.
  borderBox( renderer, x*sz, y*sz,
             sz, sz, cellBorderColor, color());
    
  char str[255]; // plenty of space.
    
  memset(str, '\0', 255);
  n = sprintf(str, "[%d %d]", this->x, this->y);
  drawText(renderer, atlas, x * sz + 4, y * sz + 4, str);
    
  memset(str, '\0', n);
  n = sprintf(str, "%s", instructionName().c_str());
  drawText(renderer, atlas,
           x * sz + 4,
           y * sz + 16, str);
    
  // render the value of the data register
  memset(str, '\0', n);
  n = sprintf(str, "%d", dataReg);
  drawText(renderer, atlas, x * sz + sz/2, y * sz + sz/2, str);
      
  // render the text value of the optical row register.
  memset(str, '\0', n);
  n = sprintf(str, "%d", rowReg);
  drawText(renderer, atlas,
           x * sz + sz/2 + sz/4,
           y * sz + sz/2, str);

  // render the text value of the optical column register.
  memset(str, '\0', n);
  n = sprintf(str, "%d", colReg); 
  drawText(renderer, atlas,
           x * sz + sz/2,
           y * sz + sz/2 + sz/4, str);

  // draw an arrow in the direction of the heading, upper right.
  memset(str, '\0', n);
  n = sprintf(str, "%c", headingToChar(cfg.heading)); 
  drawText(renderer, atlas,
           x * sz + sz - 8,
           y * sz + 4,
           str );

  // if the cell is selected then blink.
  if (selected && oddMoment()) {
    borderBox( renderer, x*sz, y*sz,
               sz, sz,
               (SDL_Color){0, 0, 0, 0}, (SDL_Color){0, 0xff, 0, 0x44});
  }
}

// | L | R | F | B | Heading | f(a, b) |
// |---+---+---+---+---------+---------|
// | a | b |   |   | North   | f(L, R) |
// | a |   | b |   | North   | f(L, F) |
// | a |   |   | b | North   | f(L, B) |
// |   | b | a |   | North   | f(F, R) |
// |   | b |   | a | North   | f(B, R) |
// |   |   | a | b | North   | f(F, B) |
// | a |   |   |   | North   | f(L)    |
// |   | a |   |   | North   | f(R)    |
// |   |   | a |   | North   | f(F)    |
// |   |   |   | a | North   | f(B)    |

Way
Cell::getArgWay1() {
  Dir d;
  switch(cfg.inputPorts.type) {
    // this is nasty, must be changed.
  case ONE_PORT_CFG: {
    d = cfg.inputPorts.value.inputOnePort.input;
    break;
  }
  case TWO_PORT_CFG: {
    d = cfg.inputPorts.value.inputTwoPort.leftInput;
    break;  // just in case another port configuration is introduced.
  }}
  return wayFromHeading(cfg.heading, d);
}

Way
Cell::getArgWay2() {
  Dir d;
  switch(cfg.inputPorts.type) {
  case ONE_PORT_CFG:
    die("This cell doesn't not support a second input argument");
  case TWO_PORT_CFG:
    d = cfg.inputPorts.value.inputTwoPort.rightInput;
    break; // just in case another port configuration is introduced.
  }
  return wayFromHeading(cfg.heading, d);
}

// DONT need to validate cell config yet, check for bit errors, this isn't a bitlevel
// representation. Using types to maintain sanity at the moment.


// self.select = function()
//    self.selected = true
// end


// self.deselect = function()
//    self.selected = false
// end

// self.setBroadcast = function(bool)
//    self.broadcasting = bool
//    self.listening = not bool
// end

// self.setListen = function(bool)
//    self.listening = bool
//    self.broadcasting = not bool
// end

// self.borderColor = function()
//    if self.selected then
//       return {0x30, 0x40, 0xFF, 0xFF}
//    else 
//       return {0x00, 0x00, 0x00, 0xFF}
//    end
// end

// self.SWAPDR = function()
//    tmp = self.rowReg
//    self.rowReg = self.data
//    self.data = tmp
// end
