#include "shapes/rectangle.h"

static void rectangle_getTransformedCorners(rectangle_s* rectangle, vec2_s* corners)
{
    float width = rectangle->size.v[X];
    float height = rectangle->size.v[Y];

    /*
    0:    0, 0
    1:    w, 0
    2:    w, h
    3:    0, h
    */

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

static void projectRectangle(vec2_s* corners, vec2_s axis, float* min, float* max)
{
    *min = glm_vec2_dot(corners[0].v, axis.v);
    *max = *min;

    for (int i = 1; i < 4; i++) {
        float projection = glm_vec2_dot(corners[i].v, axis.v);
        if (projection < *min) *min = projection;
        if (projection > *max) *max = projection;
    }
}

bool rectangle_checkCollisionRectangle(rectangle_s* rectA, rectangle_s* rectB)
{
    vec2_s cornersA[4], cornersB[4];
    vec2_s axes[8];

    rectangle_getTransformedCorners(rectA, cornersA);
    rectangle_getTransformedCorners(rectB, cornersB);

    for (int i = 0; i < 4; i++) {
        int next = (i + 1) % 4;
        vec2_s edge;
        glm_vec2_sub(cornersA[next].v, cornersA[i].v, edge.v);
        vec2_s axis = { -edge.v[Y], edge.v[X] };
        glm_vec2_normalize_to(axis.v, axis.v);
        glm_vec2_copy(axis.v, axes[i].v);
    }

    for (int i = 0; i < 4; i++) {
        int next = (i + 1) % 4;
        vec2_s edge;
        glm_vec2_sub(cornersB[next].v, cornersB[i].v, edge.v);
        vec2_s axis = { -edge.v[Y], edge.v[X] };
        glm_vec2_normalize_to(axis.v, axis.v);
        glm_vec2_copy(axis.v, axes[i + 4].v);
    }

    for (int i = 0; i < 8; i++) {
        float minA, maxA;
        projectRectangle(cornersA, axes[i], &minA, &maxA);
        float minB, maxB;
        projectRectangle(cornersB, axes[i], &minB, &maxB);
        if (maxA < minB || maxB < minA) return false;
    }

    return true;
}

bool rectangle_intersects(rect_float_s* rect1, rect_float_s* rect2) {
    // Check if one rectangle is to the left of the other
    if (rect1->left + rect1->width <= rect2->left || rect2->left + rect2->width <= rect1->left) {
        return false;
    }
    // Check if one rectangle is above the other
    if (rect1->top + rect1->height <= rect2->top || rect2->top + rect2->height <= rect1->top) {
        return false;
    }
    // If none of the conditions for separation are met, the rectangles intersect
    return true;
}


