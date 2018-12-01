#pragma once

#include <string>
#include <iostream>

using namespace std;

class Err {
public:
  string msg;
  string file;
  int line;    
  string func;
};

class ErrorStack {  
  static const int STACK_MAX = 512;
private:  
  Err items[STACK_MAX]; 
  int stackIdx;
  
  Err* top();
public:
  ErrorStack();
  void pushErr(Err e);
  void dump();
  string topMsg();
};

// -------------------------------------------------------------------------------------------------
// GLOBAL error stack.
// TODO improve perr to accept var args

extern ErrorStack _estack; // err.c

#define perr(errmsg) { \
        Err e = { .msg = errmsg, .file = __FILE__, .line = __LINE__, .func = __FUNCTION__ }; \
        _estack.pushErr(e);                                                     \
  };

#define nullDieMsg(ptr, msg) { if (ptr==NULL) { perr(msg); _estack.dump(); } }
#define nullDie(ptr) { nullDieMsg(ptr, "got null pointer"); }
#define die(msg) { perr(msg); _estack.dump(); exit(1); }


#define eerr(e, msg) { throw runtime_error(string(e.what()) + string(msg)); }
#define terr(msg) { throw runtime_error(msg); }

