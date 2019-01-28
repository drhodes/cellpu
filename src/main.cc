#include <iostream>

#include "app.hh"
#include "global.hh"

int main(void) {
  App app;
  app.eventLoop();
  std::cout << "Quitting normally. cya!" << endl;
  return 0;
}

// memory leaks.
// SUMMARY: AddressSanitizer: 995237 byte(s) leaked in 772 allocation(s).

// I think these are from SDL internals.
