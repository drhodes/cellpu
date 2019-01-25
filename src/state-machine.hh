#pragma once

#include <iostream>
#include <typeinfo>
#include <vector>

#include "err.hh"

using namespace std;

class StateMachine {
  struct Connecting {};
  struct Connected {};
  struct Disconnecting {};
  struct Disconnected {};

  struct MouseDown {};
  struct MouseUp {};
};
