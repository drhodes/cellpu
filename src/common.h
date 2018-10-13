// @file
// @brief types used everywhere.

#ifndef COMMON_H
#define COMMON_H

typedef enum { N, E, S, W } Way;

typedef struct { 
    Way n, e, s, w;
} DirVec;

typedef struct {
    int x, y;
} Loc;


#endif // COMMON_H
