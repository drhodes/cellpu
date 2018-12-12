#pragma once

#include <vector>
#include <iostream>
#include <typeinfo>

#include "err.hh"

using namespace std;

// why not do this in lua!
// 

// template <class T>
// string show(const T &obj);

/*
template <class S, class T>
class Transition {
private:
  S m_src;
  T m_trigger;
  S m_tgt;

public: 
  Transition(T trigger, S src, S tgt) :
    m_src(src), m_trigger(trigger), m_tgt(tgt) {}
  
  const S getTarget() const { return m_tgt; }
  const T getTrigger() const { return m_trigger; }
  const S getSource() const { return m_src; }
};

template <class S, class T>
class StateMachine {
private:
  S m_curState;
  std::string m_name;
  std::vector<Transition<S, T>> m_transitions;
  
public:
  StateMachine<S, T>(string name) {
    m_name = name;
  }
  
  ~StateMachine<S, T>() {
    cerr << "Destroying state machine." << std::endl;
  }
  
  void addTransition(T trigger, S src, S tgt) {
    Transition<S, T> t(trigger, src, tgt);
    m_transitions.push_back(t);    
  }
  
  void startAt(S startState) {
    m_curState = startState;
  }

  void fire(T trigger) {
    for (auto t : m_transitions) { 
      if (t.getSource() == m_curState && t.getTrigger == trigger) {
        m_curState = t.getTarget();
        return;
      }
    }
    die("Could not fire state machine, transition not found for current state");
  }

};


*/
