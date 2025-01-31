#ifndef SHADER_H
#define SHADER_H

#include "main.h"
#include "Window/window.h"

typedef struct shader_s {
    GLuint program;
} shader_s;

static char *read_file(const char *filepath);
shader_s *shader_create(window_s* window, const char *vs_filepath, const char *fs_filepath);

void shader_use(shader_s *shader);
GLuint shader_get(shader_s *shader);
void shader_delete(shader_s *shader);

void shader_setortho(shader_s *shader, int width, int height);
void shader_mat4fv(shader_s *shader, const char *name, mat4 matrix);
void shader_vec4f(shader_s *shader, const char *name, float x, float y, float z, float w);
void shader_vec3f(shader_s *shader, const char *name, float x, float y, float z);
void shader_vec2f(shader_s *shader, const char *name, float x, float y);
void shader_1f(shader_s *shader, const char *name, float x);
void shader_1i(shader_s *shader, const char *name, int x);
void shader_bool(shader_s *shader, const char *name, bool x);

#endif /* SHADER_H */
