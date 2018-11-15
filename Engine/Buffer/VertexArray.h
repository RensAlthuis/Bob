#pragma once
#include <glad/glad.h>
#include <memory>
#include <vector>
#include "VertexBuffer.h"
#include "ElementBuffer.h"

namespace Engine
{
class VertexArray
{
private:
	std::vector<VertexBuffer*> buffers;
	ElementBuffer* ebo;
  public:
	GLuint ID;
	VertexArray();
	~VertexArray();
	void addBuffer(VertexBuffer* vbo, int index);
	void setEBO(ElementBuffer* ebo);
	inline void bind() { glBindVertexArray(ID); }
	inline void unbind() { glBindVertexArray(0); }
	inline int ElementCount(){return ebo->elementCount;}
};

}; // namespace Engine