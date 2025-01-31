#include "core/ebo.h"

ebo_t ebo_create()
{
    ebo_t ebo;
    glGenBuffers(1, &ebo);
    return ebo;
}

void ebo_bind(ebo_t ebo)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void ebo_data(GLsizeiptr size, const void *data)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void ebo_subdata(GLintptr offset, GLsizeiptr size, const void *data)
{
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

void ebo_unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ebo_delete(ebo_t ebo)
{
    glDeleteBuffers(1, &ebo);
}
