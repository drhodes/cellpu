#ifndef OPTICAL_CTL_H
#define OPTICAL_CTL_H

typedef enum { Blocking = 1,
               Receiving = 2,
               Ignoring = 4,
               Relaying = 8,
} OpticalState;

typedef struct { 
    OpticalState N, S, E, W;    
} OpticalFourWay;

typedef struct {
    // GridLoc from, to;
} OpticalSegment;

#endif // OPTICAL_CTL_H
