#ifndef TEXTURE_H
#define TEXTURE_H

#include "main.h"
#include "shader.h"

typedef GLuint texture_t;

typedef struct texture_s
{
    texture_t id;
    int width;
    int height;
    int channels_in_file;
    char *path;
} texture_s;

texture_s *texture_create(char* path);
void texture_bind(texture_t texture);
void texture_parameter(texture_s* texture, GLint xAxis, GLint yAxis, GLint filterMin, GLint filterMag);
void texture_activate(texture_t texture, int index, shader_s* shader);
void texture_unbind();
void texture_delete(texture_s* texture);
texture_s* texture_load(char* path);

#endif /* TEXTURE_H */
