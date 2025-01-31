#ifndef RECT_H
#define RECT_H

#include "core/vec.h"
typedef struct rect_float_s {
    float top;
    float left;
    float width;
    float height;
} rect_float_s;

bool rect_floatIntersects(rect_float_s* rectA, rect_float_s* rectB);

#endif /* RECT_H */
