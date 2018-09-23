#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(GLfloat* data, unsigned int length, unsigned int elementCount):
    elementCount(elementCount)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * length, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
}
