#pragma once
#include <glad/glad.h>


namespace Engine{
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

};