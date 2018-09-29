#pragma once
#include <glad/glad.h>

class VertexBuffer
{
  public:
	GLuint ID;
	unsigned int elementCount;
	unsigned int elementLength;
	VertexBuffer(GLfloat *data, unsigned int nElements, unsigned int elementLength);
	~VertexBuffer();

	void bind();
	void unbind();
};
