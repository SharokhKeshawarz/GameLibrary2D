#ifndef EBO_H
#define EBO_H

#include "main.h"

typedef GLuint ebo_t;

ebo_t ebo_create();
void ebo_bind(ebo_t vbo);
void ebo_data(GLsizeiptr size, const void *data);
void ebo_subdata(GLintptr offset, GLsizeiptr size, const void *data);
void ebo_unbind();
void ebo_delete(ebo_t vbo);

#endif /* EBO_H */
