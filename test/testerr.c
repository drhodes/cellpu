
#include "stdio.h"
#include "../err.h"


int main() {
    perr("e1");
    perr("e2");
    perr("e3");
    perr("e4");
    reportUnwind();
}
