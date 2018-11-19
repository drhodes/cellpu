// @file
// @brief This file is marvelous.

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "err.h"

using namespace std;

ErrorStack _estack;

ErrorStack::ErrorStack() {
  stackIdx = 0;
}

void
ErrorStack::pushErr(Err e) {
  if (stackIdx < STACK_MAX) {
    stackIdx++;
    *top() = e;
  } else {
    die("Exhausted error stack, TODO something more reasonable here");
  }
}

void
ErrorStack::dump() {
  while (stackIdx >= 1) {
    cerr << top()->msg << " (" << top()->file << ", " << top()->line << ")" << endl;
    stackIdx--;
  }
}

Err*
ErrorStack::top() {
  return &items[stackIdx];
}

string
ErrorStack::topMsg() {
  return items[stackIdx].msg;
}
