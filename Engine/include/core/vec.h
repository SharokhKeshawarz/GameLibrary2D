#ifndef VEC_H
#define VEC_H

#include "cglm/cglm.h"

#define DEG 0
#define RAD 1
#define X 0
#define Y 1
#define Z 2
#define W 3

typedef union vec2_s {
    struct {
        float x;
        float y;
    };
    vec2 v;
} vec2_s;

typedef union vec3_s {
    struct {
        float x;
        float y;
        float z;
    };
    vec3 v;
} vec3_s;

typedef union vec4_s {
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    vec4 v;
} vec4_s;

#endif /* VEC_H */
