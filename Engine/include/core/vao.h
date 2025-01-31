#ifndef VAO_H
#define VAO_H

#include "main.h"

typedef GLuint vao_t;

vao_t vao_create();
void vao_bind(vao_t vao);
void vao_attribpointer(GLuint index, GLuint size, GLuint stride, GLuint pointer);
void vao_unbind();
void vao_delete(vao_t vao);

#endif /* VAO_H */
