#include "shapes/rectangle.h"

static void rectangle_updateModel(rectangle_s* rectangle)
{
    glm_mat4_identity(rectangle->model);

    glm_translate(rectangle->model, (vec3){rectangle->position.v[X], rectangle->position.v[Y], 0.0f});

    glm_translate(rectangle->model, (vec3){rectangle->origin.v[X], rectangle->origin.v[Y], 0.0f});
    glm_rotate_z(rectangle->model, rectangle->rotation.v[RAD], rectangle->model);
    glm_scale(rectangle->model, (vec3){rectangle->scale.v[X], rectangle->scale.v[Y], 1.0f});
    glm_translate(rectangle->model, (vec3){-rectangle->origin.v[X], -rectangle->origin.v[Y], 0.0f});
}

void rectangle_setOrigin(rectangle_s* rectangle, vec2_s origin)
{
    glm_vec2_copy(origin.v, rectangle->origin.v);

    rectangle_updateModel(rectangle);
}

void rectangle_setSize(rectangle_s* rectangle, vec2_s size)
{
    glm_vec2_copy(size.v, rectangle->size.v);
    rectangle->rect.width = size.v[X];
    rectangle->rect.height = size.v[Y];

    /*
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
    */
    rectangle->vertices[4] = size.v[X];
    rectangle->vertices[8] = size.v[X];
    rectangle->vertices[9] = size.v[Y];
    rectangle->vertices[13] = size.v[Y];

    vbo_bind(rectangle->vbo);
    vbo_subdata(0, sizeof(rectangle->vertices), rectangle->vertices);
    vbo_unbind();
    rectangle_updateModel(rectangle);
}

void rectangle_setColor(rectangle_s* rectangle, vec4_s color)
{
    glm_vec4_copy(color.v, rectangle->color.v);
}

void rectangle_setScale(rectangle_s* rectangle, vec2_s scale)
{
    glm_vec2_copy(scale.v, rectangle->scale.v);

    rectangle_updateModel(rectangle);
}

void rectangle_setScaleUni(rectangle_s* rectangle, float scale)
{
    rectangle->scale.v[X] = scale;
    rectangle->scale.v[Y] = scale;

    rectangle_updateModel(rectangle);
}

void rectangle_setRotation(rectangle_s* rectangle, float angle)
{
    rectangle->rotation.v[DEG] = angle;
    rectangle->rotation.v[RAD] = glm_rad(angle);

    rectangle_updateModel(rectangle);
}

void rectangle_setPosition(rectangle_s* rectangle, vec2_s position)
{
    glm_vec2_copy(position.v, rectangle->position.v);

    rectangle_updateModel(rectangle);
}

void rectangle_move(rectangle_s* rectangle, vec2_s displacement)
{
    rectangle->position.v[X] += displacement.v[X];
    rectangle->position.v[Y] += displacement.v[Y];

    rectangle_updateModel(rectangle);
}

void rectangle_setOutlineColor(rectangle_s* rectangle, vec4_s color) {
    glm_vec4_copy(color.v, rectangle->outlineColor.v);
}

void rectangle_setOutlineThickness(rectangle_s* rectangle, float thickness) {
    rectangle->outlineThickness = thickness;
    rectangle->hasOutline = true;
}

void rectangle_setTexture(rectangle_s* rectangle, texture_s* texture)
{ 
    if (!texture) {
        fprintf(stderr, "Error: Null texture provided to rectangle_setTexture.\n");
        return;
    }

    rectangle->textureID = texture->id;
    rectangle->hasTexture = true;

    // Set default texture coordinates (full texture)
    rectangle->vertices[2]  = 0.0f; // Bottom-left (U)
    rectangle->vertices[3]  = 0.0f; // Bottom-left (V)
    rectangle->vertices[6]  = 1.0f; // Bottom-right (U)
    rectangle->vertices[7]  = 0.0f; // Bottom-right (V)
    rectangle->vertices[10] = 1.0f; // Top-right (U)
    rectangle->vertices[11] = 1.0f; // Top-right (V)
    rectangle->vertices[14] = 0.0f; // Top-left (U)
    rectangle->vertices[15] = 1.0f; // Top-left (V)

    // Update the vertex buffer
    vbo_bind(rectangle->vbo);
    vbo_subdata(0, sizeof(rectangle->vertices), rectangle->vertices);
    vbo_unbind();
}

void rectangle_setTextureRect(rectangle_s* rectangle, texture_s* texture, rect_float_s rect, FlipFlag flip)
{
    if (!texture) {
        fprintf(stderr, "Error: Null texture provided to rectangle_setTextureRect.\n");
        return;
    }

    // Validate texture rect bounds
    if (rect.left < 0 || rect.top < 0 ||
        rect.left + rect.width > texture->width ||
        rect.top + rect.height > texture->height) {
        fprintf(stderr, "Error: Rect dimensions out of texture bounds.\n");
        return;
    }

    rectangle->textureID = texture->id;
    rectangle->hasTexture = true;

    float textureWidth = texture->width;
    float textureHeight = texture->height;

    // Normalize texture coordinates
    float u1 = rect.left / textureWidth;
    float v1 = rect.top / textureHeight;
    float u2 = (rect.left + rect.width) / textureWidth;
    float v2 = (rect.top + rect.height) / textureHeight;

    // Apply flipping
    if (flip & FLIP_HORIZONTAL) {
        float temp = u1; u1 = u2; u2 = temp;
    }
    if (flip & FLIP_VERTICAL) {
        float temp = v1; v1 = v2; v2 = temp;
    }

    // Update texture coordinates
    rectangle->vertices[2]  = u1; // Bottom-left (U)
    rectangle->vertices[3]  = v1; // Bottom-left (V)
    rectangle->vertices[6]  = u2; // Bottom-right (U)
    rectangle->vertices[7]  = v1; // Bottom-right (V)
    rectangle->vertices[10] = u2; // Top-right (U)
    rectangle->vertices[11] = v2; // Top-right (V)
    rectangle->vertices[14] = u1; // Top-left (U)
    rectangle->vertices[15] = v2; // Top-left (V)

    // Update the vertex buffer
    vbo_bind(rectangle->vbo);
    vbo_subdata(0, sizeof(rectangle->vertices), rectangle->vertices);
    vbo_unbind();
    texture_bind(rectangle->textureID);
}

