#ifndef OPTICAL_CTL_C
#define OPTICAL_CTL_C

#include "optical-ctl.hh"


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

bool opticalCtlConfig(OpticalCtl *oc, Dir src, Dir tgt) {
    if (src == tgt) {
        perr ("tried to set the source of target port of an optical ctl to itself");
        return false;
    }
    switch (tgt) {
    case N: oc->portN.output.src = src;
    case S: oc->portS.output.src = src;
    case E: oc->portE.output.src = src;
    case W: oc->portW.output.src = src;
    }
    return true;
}


#endif // OPTICAL_CTL_C
