#ifndef BBOX_C
#define BBOX_C

#include "bbox.h"

bool
bboxContains(BBox bb, int x, int y) {
    return ( bb.left <= x &&
             x <= bb.left + bb.width &&
             bb.top <= y &&
             y <= bb.top + bb.height );
}


#endif // BBOX
