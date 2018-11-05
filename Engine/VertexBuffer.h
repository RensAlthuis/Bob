#pragma once
#include <glad/glad.h>

namespace Engine
{
class VertexBuffer
{
public:
	GLuint ID;
	unsigned int elementCount;
	unsigned int elementLength;
	VertexBuffer(GLfloat *data, unsigned int nElements, unsigned int elementLength);
	~VertexBuffer();

	inline void bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); }
	inline void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
};

}; // namespace Engine