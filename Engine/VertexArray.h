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
	std::vector<std::unique_ptr<VertexBuffer>> buffers;
	std::unique_ptr<ElementBuffer> ebo;
  public:
	GLuint ID;
	VertexArray();
	~VertexArray();
	void addBuffer(std::unique_ptr<VertexBuffer> vbo, int index);
	void setEBO(std::unique_ptr<ElementBuffer > ebo);
	inline void bind() { glBindVertexArray(ID); }
	inline void unbind() { glBindVertexArray(0); }
	inline int ElementCount(){return ebo->elementCount;}
};

}; // namespace Engine