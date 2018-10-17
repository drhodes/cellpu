// @file
// @brief types used everywhere.

#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef enum { N = 0,
               E = 1,
               S = 2,
               W = 4} Way;

typedef int DirFlags;

typedef struct { 
    Way n, e, s, w;
} DirVec;


// typedef struct { 
//     Way n, e, s, w;
// } DirVec;



typedef struct {
    int x, y;
} Loc;


bool oddSecond();



#endif // COMMON_H
