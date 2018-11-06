#include "VertexArray.h"
#include <iostream>

namespace Engine
{

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}

void VertexArray::addBuffer(std::unique_ptr<VertexBuffer> buffer, int index)
{
    bind();
    buffer->bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, buffer->elementLength, GL_FLOAT, GL_FALSE, 0, (void *)0);
    buffer->unbind();
    unbind();
    buffers.push_back(std::move(buffer));
}

void VertexArray::setEBO(std::unique_ptr<ElementBuffer> buffer)
{
    ebo = std::move(buffer);
    bind();
    ebo->bind();
    unbind();
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &ID);
}

}; // namespace Engine