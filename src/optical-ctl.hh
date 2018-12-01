#ifndef OPTICAL_CTL_H
#define OPTICAL_CTL_H

#include "err.hh"
#include "dir.hh"
#include <stdbool.h>

/// \struct Optical output is asdf asd asdf asdf asdf asdf sdf asdf
/// asdf asd asd asdf asdf asdf sdf
typedef struct OpticalOutput {
    Dir src;
    bool driven;    
} OpticalOutput;

char *showOpticalOutput();


typedef struct OpticalInput {
    bool on;
} OpticalInput;


typedef union OpticalPort {
    OpticalInput input;
    OpticalOutput output;
} OpticalPort;

OpticalPort opticalPortInput();
OpticalPort opticalPortOutput();

typedef struct OpticalCtl {
    OpticalPort portN, portE, portS, portW;
} OpticalCtl;

bool opticalCtlConfig(OpticalCtl *oc, Dir src, Dir tgt);

OpticalCtl opticalCtlNE();
OpticalCtl opticalCtlSW();

typedef struct {
    // GridLoc from, to;
} OpticalSegment;

#endif // OPTICAL_CTL_H
