#pragma once
#include <glad/glad.h>
#include "VertexBuffer.h"
#include "ElementBuffer.h"

class VertexArray
{
public:

	GLuint ID;
	VertexArray();
	~VertexArray();
	void addBuffer(VertexBuffer* vbo, int index);
	void setEBO(ElementBuffer* ebo);
	void bind();
	void unbind();
};

