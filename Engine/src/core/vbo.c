#include "core/vbo.h"

vbo_t vbo_create()
{
    vbo_t vbo;
    glGenBuffers(1, &vbo);
    return vbo;
}

void vbo_bind(vbo_t vbo)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void vbo_data(GLsizeiptr size, const void *data)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void vbo_subdata(GLintptr offset, GLsizeiptr size, const void *data)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void vbo_unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo_delete(vbo_t vbo)
{
    glDeleteBuffers(1, &vbo);
}
