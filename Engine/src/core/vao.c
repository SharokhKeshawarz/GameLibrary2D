#include "core/vao.h"

vao_t vao_create()
{
    vao_t vao;
    glGenVertexArrays(1, &vao);
    return vao;
}

void vao_bind(vao_t vao)
{
    glBindVertexArray(vao);
}

void vao_attribpointer(GLuint index, GLuint size, GLuint stride, GLuint pointer)
{
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(pointer * sizeof(float)));
    glEnableVertexAttribArray(index);
}

void vao_unbind()
{
    glBindVertexArray(0);
}

void vao_delete(vao_t vao)
{
    glDeleteVertexArrays(1, &vao);
}
