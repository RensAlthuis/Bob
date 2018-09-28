#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}

void VertexArray::bind()
{
    glBindVertexArray(ID);
}

void VertexArray::unbind()
{
    glBindVertexArray(ID);
}

void VertexArray::addBuffer(VertexBuffer *vbo, int index)
{
    bind();
    vbo->bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, vbo->elementCount, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * vbo->elementCount, (void *)0);
    vbo->unbind();
    unbind();
}

void VertexArray::setEBO(ElementBuffer *ebo)
{
    bind();
    ebo->bind();
    unbind();
}

VertexArray::~VertexArray()
{
}
