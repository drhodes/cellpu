#ifndef OPTICAL_CTL_C
#define OPTICAL_CTL_C

#include "optical-ctl.h"


OpticalPort opticalPortOutput(Dir src) {    
    OpticalPort p = { .output = { .src = src, .driven = true }};
    return p;
}

OpticalPort opticalPortInput() {    
    OpticalPort p = { .input = { .on = false }};
    return p;
}

OpticalCtl opticalCtlNE() {
    OpticalCtl oc = { .portN = opticalPortOutput(S),
                      .portE = opticalPortOutput(W),
                      .portS = opticalPortInput(),
                      .portW = opticalPortInput() };
    return oc;
}


#endif // OPTICAL_CTL_C
