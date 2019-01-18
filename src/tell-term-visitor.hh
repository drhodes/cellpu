#include "visit.hh"
#include "term.hh"
  
class TellTermVisitor : public BaseVisitor 
{
private:
  string m_str;
public:  
  TellTermVisitor(string str) {
    m_str = str;
  }  
  void visit(Term &term) {
    term.putInput(m_str);
  }
};
