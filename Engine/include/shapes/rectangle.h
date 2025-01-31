#ifndef RECTANGLE_H
#define RECTANGLE_H
    
#include "core/main.h"
#include "core/shader.h"
#include "core/vao.h"
#include "core/vbo.h"
#include "core/ebo.h"
#include "core/log.h"
#include "core/vec.h"
#include "core/texture.h"
#include "shapes/rect.h"
#include "Window/window.h"

typedef struct rectangle_s {
    vao_t vao;
    vbo_t vbo;
    ebo_t ebo;

    mat4 model;
    GLfloat vertices[16];
    GLuint indices[6];
    rect_float_s rect;
    
    vec4_s color;
    vec2_s size;
    vec2_s scale;
    vec2_s rotation;
    vec2_s position;
    vec2_s origin;

    vec4_s outlineColor;
    float outlineThickness;
    bool hasOutline;

    GLuint textureID;
    bool hasTexture;
} rectangle_s;

typedef enum {
    FLIP_NONE = 0,
    FLIP_HORIZONTAL = 1,
    FLIP_VERTICAL = 2,
    FLIP_BOTH = 3
} FlipFlag;

rectangle_s *rectangle_create(void);
void rectangle_draw(window_s* window, rectangle_s* rectangle, shader_s* shader);
void rectangle_destroy(rectangle_s* rectangle);

void rectangle_setOrigin(rectangle_s* rectangle, vec2_s origin);
void rectangle_setSize(rectangle_s* rectangle, vec2_s size);
void rectangle_setColor(rectangle_s* rectangle, vec4_s color);
void rectangle_setScale(rectangle_s* rectangle, vec2_s scale);
void rectangle_setScaleUni(rectangle_s* rectangle, float scale);
void rectangle_setRotation(rectangle_s* rectangle, float angle);
void rectangle_setPosition(rectangle_s* rectangle, vec2_s position);
void rectangle_move(rectangle_s* rectangle, vec2_s displacement);
void rectangle_setOutlineColor(rectangle_s* rectangle, vec4_s color);
void rectangle_setOutlineThickness(rectangle_s* rectangle, float thickness);
rect_float_s rectangle_getLocalBounds(rectangle_s* rectangle);
rect_float_s rectangle_getGlobalBounds(rectangle_s* rectangle);
bool rectangle_checkCollisionRectangle(rectangle_s* rectA, rectangle_s* rectB);

vec2_s rectangle_getOrigin(rectangle_s* rectangle);
vec2_s rectangle_getSize(rectangle_s* rectangle);
vec4_s rectangle_getColor(rectangle_s* rectangle);
vec2_s rectangle_getScale(rectangle_s* rectangle);
vec2_s rectangle_getAngle(rectangle_s* rectangle);
vec2_s rectangle_getPosition(rectangle_s* rectangle);

void rectangle_setTexture(rectangle_s* rectangle, texture_s* texture);
void rectangle_setTextureRect(rectangle_s* rectangle, texture_s* texture, rect_float_s rect, FlipFlag flip);
bool rectangle_intersects(rect_float_s* rect1, rect_float_s* rect2);

void rectangle_draw_texture_rect(texture_s* texture, rect_float_s rect, shader_s* shader);
#endif
