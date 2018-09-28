#pragma once
#include <glad/glad.h>

class VertexBuffer
{
  public:
	GLuint ID;
	unsigned int elementCount;
	VertexBuffer(GLfloat *data, unsigned int length, unsigned int elementCount);
	~VertexBuffer();

	void bind();
	void unbind();
};
