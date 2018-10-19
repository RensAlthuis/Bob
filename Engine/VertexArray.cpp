#include "VertexArray.h"
#include <iostream>


namespace Engine{

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
    glBindVertexArray(0);
}

void VertexArray::addBuffer(VertexBuffer *vbo, int index)
{
    bind();
    vbo->bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, vbo->elementLength, GL_FLOAT, GL_FALSE, 0, (void *)0);
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
    glDeleteVertexArrays(1, &ID);
}

};