#include "shapes/rectangle.h"
#include "shapes/rect.h"

static void rectangle_getTransformedCorners(rectangle_s* rectangle, vec2_s* corners)
{
    float width = rectangle->size.v[X];
    float height = rectangle->size.v[Y];

    corners[0].v[0] = 0.0f;
    corners[0].v[1] = 0.0f;
    corners[1].v[0] = width;
    corners[1].v[1] = 0.0f;
    corners[2].v[0] = width;
    corners[2].v[1] = height;
    corners[3].v[0] = 0.0f;
    corners[3].v[1] = height;

    for (int i = 0; i < 4; i++) {
        corners[i].v[X] *= rectangle->scale.v[X];
        corners[i].v[Y] *= rectangle->scale.v[Y];
    }

    float cosAngle = cosf(rectangle->rotation.v[RAD]);
    float sinAngle = sinf(rectangle->rotation.v[RAD]);

    for (int i = 0; i < 4; i++) {
        float x = corners[i].v[X];
        float y = corners[i].v[Y];

        corners[i].v[X] = cosAngle * x - sinAngle * y + rectangle->position.v[X];
        corners[i].v[Y] = sinAngle * x + cosAngle * y + rectangle->position.v[Y];
    }
}

rect_float_s rectangle_getLocalBounds(rectangle_s* rectangle)
{
    rect_float_s bounds;
    bounds.left = 0.0f;
    bounds.top = 0.0f;
    bounds.width = rectangle->size.v[X];
    bounds.height = rectangle->size.v[Y];
    return bounds;
}

rect_float_s rectangle_getGlobalBounds(rectangle_s* rectangle)
{
    rect_float_s bounds;
    vec2_s corners[4];

    rectangle_getTransformedCorners(rectangle, corners);
    
    float minX = corners[0].v[X], maxX = corners[0].v[X];
    float minY = corners[0].v[Y], maxY = corners[0].v[Y];

    for (int i = 1; i < 4; i++) {
        if (corners[i].v[X] < minX) minX = corners[i].v[X];
        if (corners[i].v[X] > maxX) maxX = corners[i].v[X];
        if (corners[i].v[Y] < minY) minY = corners[i].v[Y];
        if (corners[i].v[Y] > maxY) maxY = corners[i].v[Y];
    }

    bounds.left = minX;
    bounds.top = minY;
    bounds.width = maxX - minX;
    bounds.height = maxY - minY;
    return bounds;
}

vec2_s rectangle_getOrigin(rectangle_s* rectangle)
{
    return rectangle->origin;
}

vec2_s rectangle_getSize(rectangle_s* rectangle)
{
    return rectangle->size;
}

vec4_s rectangle_getColor(rectangle_s* rectangle)
{
    return rectangle->color;
}

vec2_s rectangle_getScale(rectangle_s* rectangle)
{
    return rectangle->scale;
}

vec2_s rectangle_getAngle(rectangle_s* rectangle)
{
    return rectangle->rotation;
}

vec2_s rectangle_getPosition(rectangle_s* rectangle)
{
    return rectangle->position;
}


