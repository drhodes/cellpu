#ifndef BBOX_H
#define BBOX_H

#include <stdbool.h> 

typedef struct {
    int top, left, height, width;
} BBox;

bool bboxContains(BBox bb, int x, int y);


#endif // BBOX

