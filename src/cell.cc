#include "cell.hh"
#include "draw.hh"
#include "err.hh"
#include "instruction.hh"
#include "state-machine.hh"

using namespace std;

Cell::Cell(int col, int row) {
  m_col = col;
  m_row = row;
  m_zoom = 1;
  m_selected = false;
  m_broadcasting = false;
  m_listening = false;
  m_rowReg = 0;
  m_colReg = 0;
  m_dataReg = 0;
  m_value = 0;
  m_inst = make_shared<NOOP>();
}

Cell::~Cell() {
  cerr << "Destroying Cell: x=" << m_col << ", y=" << m_row << endl;
}

void Cell::setInstruction(shared_ptr<Instruction> inst) { m_inst = inst; }

void Cell::dataReg(int n) { m_dataReg = n; }

int Cell::dataReg() { return m_dataReg; }

void Cell::selected(bool b) { m_selected = b; }

bool Cell::selected() { return m_selected; }

void Cell::setZoom(int zoom) { m_zoom = zoom; }

SDL_Color Cell::color() const {
  // change this.
  SDL_Color c = m_inst->m_color;
  return c;
}

void Cell::cycle(struct Grid *grid) {
  // the instruction needs to see the neighborhood, so it needs a
  // pointer to grid.
  // inst->op(grid, cell);
}

string Cell::instructionName() const { return m_inst->m_name; }

int Cell::size() const { return m_zoom * this->m_size; }

void Cell::render(Atlas &atlas, SDL_Renderer *renderer) const {
  int sz = this->size();
  int n = 0;

  SDL_Color cellBorderColor = color();
  cellBorderColor.r /= 2;
  cellBorderColor.g /= 2;
  cellBorderColor.b /= 2;

  if (m_selected && oddMoment()) {
    // if the cell is selected then blink.
    draw::borderBox(m_col * sz, m_row * sz, sz, sz, cellBorderColor,
                    cellBorderColor);
  } else {
    // otherwise normal color for background box.
    draw::borderBox(m_col * sz, m_row * sz, sz, sz, cellBorderColor, color());
  }

  char str[255];  // plenty of space for text.

  if (sz > 40) {  // enough room for row, col
    memset(str, '\0', 255);
    n = sprintf(str, "[%d %d]", m_col, this->m_row);
    draw::text(atlas, m_col * sz + 4, m_row * sz + 4, str);
  }

  memset(str, '\0', n);
  n = sprintf(str, "%s", instructionName().c_str());
  draw::text(atlas, m_col * sz + 4, m_row * sz + 16, str);

  // draw an arrow in the direction of the heading, upper right.
  memset(str, '\0', n);
  n = sprintf(str, "%c", headingToChar(m_cfg.heading));
  draw::text(atlas, m_col * sz + sz - 8, m_row * sz + 4, str);
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

Way Cell::getArgWay1() {
  Dir d;
  switch (m_cfg.inputPorts.type) {
    case PortCfgType::ONE_PORT: {
      d = m_cfg.inputPorts.value.inputOnePort.input;
      return wayFromHeading(m_cfg.heading, d);
    }
    case PortCfgType::TWO_PORT: {
      d = m_cfg.inputPorts.value.inputTwoPort.leftInput;
      return wayFromHeading(m_cfg.heading, d);
    }
  }
  die("unreachable code reached");
}

Way Cell::getArgWay2() {
  Dir d;
  switch (m_cfg.inputPorts.type) {
    case PortCfgType::ONE_PORT:
      die("This cell doesn't not support a second input argument");
    case PortCfgType::TWO_PORT:
      d = m_cfg.inputPorts.value.inputTwoPort.rightInput;
      return wayFromHeading(m_cfg.heading, d);
  }
  die("unreachable code reached");
}

int Cell::row() { return m_row; }
int Cell::col() { return m_col; }
