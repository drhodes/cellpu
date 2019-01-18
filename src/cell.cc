#include "cell.hh"
#include "err.hh"
#include "draw.hh"
#include "instruction.hh"
#include "state-machine.hh"

using namespace std;

Cell::Cell(int col, int row) { 
  x_ = col;
  y_ = row;
  m_zoom = 1;
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
Cell::accept(std::shared_ptr<Visitor> v) {
  v->visit(*this);
}

void
Cell::setInstruction(shared_ptr<Instruction> inst) {
  inst_ = inst;  
}

void
Cell::setSelect(bool b) {
  selected_ = b;
}

void Cell::setZoom(int zoom) { m_zoom = zoom; }

SDL_Color
Cell::color() const {
  // change this.
  SDL_Color c = inst_->m_color;
  return c;
}

void
Cell::cycle(struct Grid *grid) {
  // the instruction needs to see the neighborhood, so it needs a
  // pointer to grid. 
  // inst->op(grid, cell);
}

string
Cell::instructionName() const {
  return inst_->m_name;
}

int
Cell::size() const {
  return m_zoom * this->m_size;
}

void
Cell::render(Atlas& atlas, SDL_Renderer *renderer) const {
  int sz = this->size();
  int n = 0;

  SDL_Color cellBorderColor = color();  
  cellBorderColor.r /= 2;
  cellBorderColor.g /= 2;
  cellBorderColor.b /= 2;

  if (selected_ && oddMoment()) {     
    // if the cell is selected then blink.
    draw::borderBox( x_*sz, y_*sz, sz, sz, cellBorderColor, cellBorderColor);
  } else {
    // otherwise normal color for background box.
    draw::borderBox( x_*sz, y_*sz, sz, sz, cellBorderColor, color());
  }
    
  char str[255]; // plenty of space for text.
    
  if (sz > 40) {  // enough room for row, col
  memset(str, '\0', 255);
  n = sprintf(str, "[%d %d]", this->x_, this->y_);
  draw::text(atlas,
             x_*sz + 4,
             y_*sz + 4,
             str);
  }

  memset(str, '\0', n);
  n = sprintf(str, "%s", instructionName().c_str());
  draw::text(atlas,
             x_ * sz + 4,
             y_ * sz + 16,
             str);
  
  // draw an arrow in the direction of the heading, upper right.
  memset(str, '\0', n);
  n = sprintf(str, "%c", headingToChar(cfg_.heading)); 
  draw::text(atlas,
             (x_ * sz) + sz - 8,
             (y_ * sz) + 4,
             str );
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
