#include "cell.hh"
#include "err.hh"
#include "draw.hh"
#include "instruction.hh"
#include "state-machine.hh"

using namespace std;

Cell::Cell(int x, int y) { 
  x_ = x;
  y_ = y;
  size_ = 60;
  selected_ = false;
  broadcasting_ = false;
  listening_ = false;
  rowReg_ = 0;
  colReg_ = 0;
  dataReg_ = 0;
  value_ = 0;
  inst_ = make_shared<NOOP>();
  
  // smach = make_shared<StateMachine<CellState, CellTrans>>();
  // smach->startAt(CellState::Resting);
}

Cell::~Cell() {
  cerr << "Destroying Cell: x=" << x_ << ", y=" << y_ << endl;
}



void
Cell::setSelect(bool b) {
  selected_ = b;
}




SDL_Color
Cell::color() {
  // change this.
  SDL_Color c = {0x56, 0x56, 0x56, 0xFF};  
  return c;
}

void
Cell::cycle(struct Grid *grid) {
  // the instruction needs to see the neighborhood, so it needs a
  // pointer to grid. 
  // inst->op(grid, cell);
}

string
Cell::instructionName() {
  return inst_->m_name;
}

void
Cell::render(shared_ptr<Atlas> atlas, SDL_Renderer *renderer) {
  int sz = this->size_;
  int n = 0;

  SDL_Color cellBorderColor = {0x00, 0x00, 0x00, 0xFF};

  // background box.
  draw::borderBox( x_*sz, y_*sz, sz, sz, cellBorderColor, color());
    
  char str[255]; // plenty of space.
    
  memset(str, '\0', 255);
  n = sprintf(str, "[%d %d]", this->x_, this->y_);
  draw::text(atlas, x_ * sz + 4, y_ * sz + 4, str);
    
  memset(str, '\0', n);
  n = sprintf(str, "%s", instructionName().c_str());
  draw::text(atlas,
             x_ * sz + 4,
             y_ * sz + 16, str);
    
  // render the value of the data register
  memset(str, '\0', n);
  n = sprintf(str, "%d", dataReg_);
  draw::text(atlas, x_ * sz + sz/2, y_ * sz + sz/2, str);
      
  // render the text value of the optical row register.
  memset(str, '\0', n);
  n = sprintf(str, "%d", rowReg_);
  draw::text(atlas,
             x_ * sz + sz/2 + sz/4,
             y_ * sz + sz/2, str);

  // render the text value of the optical column register.
  memset(str, '\0', n);
  n = sprintf(str, "%d", colReg_); 
  draw::text(atlas,
             x_ * sz + sz/2,
             y_ * sz + sz/2 + sz/4, str);

  // draw an arrow in the direction of the heading, upper right.
  memset(str, '\0', n);
  n = sprintf(str, "%c", headingToChar(cfg_.heading)); 
  draw::text(atlas,
             x_ * sz + sz - 8,
             y_ * sz + 4,
             str );

  // if the cell is selected then blink.
  if (selected_ && oddMoment()) {
    draw::borderBox( x_*sz, y_*sz,
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
  switch(cfg_.inputPorts.type) {
  case PortCfgType::ONE_PORT: {
    d = cfg_.inputPorts.value.inputOnePort.input;
    return wayFromHeading(cfg_.heading, d);
  }
  case PortCfgType::TWO_PORT: {
    d = cfg_.inputPorts.value.inputTwoPort.leftInput;
    return wayFromHeading(cfg_.heading, d);
  }}
  die("unreachable code reached");
}

Way
Cell::getArgWay2() {
  Dir d;
  switch(cfg_.inputPorts.type) {
  case PortCfgType::ONE_PORT:
    die("This cell doesn't not support a second input argument");    
  case PortCfgType::TWO_PORT:
    d = cfg_.inputPorts.value.inputTwoPort.rightInput;
    return wayFromHeading(cfg_.heading, d);
  }
  die("unreachable code reached");
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
