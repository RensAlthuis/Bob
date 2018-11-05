#pragma once
#include <glad/glad.h>
#include "VertexBuffer.h"
#include "ElementBuffer.h"

namespace Engine
{
class VertexArray
{
  public:
	GLuint ID;
	VertexArray();
	~VertexArray();
	void addBuffer(VertexBuffer *vbo, int index);
	void setEBO(ElementBuffer *ebo);
	inline void bind() { glBindVertexArray(ID); }
	inline void unbind() { glBindVertexArray(0); }
};

}; // namespace Engine