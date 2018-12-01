// @file
// @brief This file is marvelous.

#include "bbox.hh"

// bool
// bboxContains(BBox bb, int x, int y) {
//     return ( bb.left <= x &&
//              x <= bb.left + bb.width &&
//              bb.top <= y &&
//              y <= bb.top + bb.height );
// }


BBox::BBox() : top(0), left(0), height(0), width(0) { }

BBox::BBox(int top, int left, int height, int width)
: top(top), left(left), height(height), width(width) { } 



bool
BBox::containsPx(int x, int y) {
    return ( left <= x &&
             x <= left + width &&
             top <= y &&
             y <= top + height );
}
