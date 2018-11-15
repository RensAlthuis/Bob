#pragma once

#include <glad/glad.h>

namespace Engine
{
class ElementBuffer
{
public:
	GLuint ID;
	unsigned int elementCount;
	ElementBuffer(GLuint *data, int length);
	~ElementBuffer();

	inline void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }
	inline void unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
};
}; // namespace Engine