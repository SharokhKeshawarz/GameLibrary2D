#ifndef VBO_H
#define VBO_H

#include "main.h"

typedef GLuint vbo_t;

vbo_t vbo_create();
void vbo_bind(vbo_t vbo);
void vbo_data(GLsizeiptr size, const void *data);
void vbo_subdata(GLintptr offset, GLsizeiptr size, const void *data);
void vbo_unbind();
void vbo_delete(vbo_t vbo);

#endif /* VBO_H */
