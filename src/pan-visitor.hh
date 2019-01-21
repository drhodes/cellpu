#include "visit.hh"
#include "grid-edit.hh"
  
class PanVisitor : public BaseVisitor 
{
private:
  string m_cmd;
public:  
  PanVisitor(string cmd) {    
    m_cmd = cmd;
  }  
  void visit(GridEditor &ge) {
    if (m_cmd == "pan-east") ge.panEast();
    if (m_cmd == "pan-west") ge.panWest();
    if (m_cmd == "pan-north") ge.panNorth();
    if (m_cmd == "pan-south") ge.panSouth();
  }
};
