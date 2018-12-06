#pragma once

#include <vector>
#include <iostream>

using namespace std;

template <class S, class T>
class Transition {
private:
  S m_src;
  T m_trigger;
  S m_tgt;

public:
  Transition(T trigger, S src, S tgt) :
    m_src(src), m_trigger(trigger), m_tgt(tgt) {}
  
};

template <class S, class T>
class StateMachine {
private:
  S m_curState;
  std::vector<Transition<S, T>> m_transitions;

public:
  StateMachine<S, T>() { }
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
};


