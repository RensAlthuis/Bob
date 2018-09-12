#pragma once

#include <glad/glad.h>

class ElementBuffer
{
public:

    GLuint ID;
	unsigned int elementCount;
	ElementBuffer(GLuint* data, int length);
	~ElementBuffer();
	void bind();
	void unbind();
};

