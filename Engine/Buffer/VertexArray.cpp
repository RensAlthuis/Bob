#include "VertexArray.h"
#include <iostream>

namespace Engine
{

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}

void VertexArray::addBuffer(VertexBuffer *buffer, int index)
{
    bind();
    buffer->bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, buffer->elementLength, GL_FLOAT, GL_FALSE, 0, (void *)0);
    buffer->unbind();
    unbind();
    buffers.push_back(buffer);
}

void VertexArray::setEBO(ElementBuffer *buffer)
{
    ebo = buffer;
    bind();
    ebo->bind();
    unbind();
}

VertexArray::~VertexArray()
{
    for (VertexBuffer *buf : buffers)
    {
        delete buf;
    }
    delete ebo;
    glDeleteVertexArrays(1, &ID);
}

}; // namespace Engine