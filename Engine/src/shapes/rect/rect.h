#include "shapes/rect.h"

bool rect_floatIntersects(rect_float_s* rectA, rect_float_s* rectB)
{
    if (rectA->left + rectA->width <= rectB->left || rectB->left + rectB->width <= rectA->left)
        return false;
    if (rectA->top + rectA->height <= rectB->top || rectB->top + rectB->height <= rectA->top)
        return false;
    return true;
}

