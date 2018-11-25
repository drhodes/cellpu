#ifndef DIR_C
#define DIR_C

#include "dir.h"

Dir dir_invert(Dir d) {
    if (d == N) return S;
    if (d == E) return W;
    if (d == S) return N;
    if (d == W) return E;
}

#endif // DIR_C
