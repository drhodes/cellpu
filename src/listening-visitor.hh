#pragma once

#include "grid-edit.hh"
#include "term.hh"
#include "visit.hh"

class ListeningVisitor : public Visitor {
 private:
  bool m_listening;

 public:
  ListeningVisitor(bool l) { m_ev = ev; }
  void visit(GridEditor &ge) { ge.listening(m_listening); }
  void visit(Term &term) { term.listening(m_listening); }
  
};
