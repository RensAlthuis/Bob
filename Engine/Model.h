#pragma once
#include "FileReader.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include "Maths/Maths.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"

namespace Engine
{
class Model
{
  private:
	struct indexStruct
	{
		int v;
		int n;
		bool operator==(const indexStruct &o) const
		{
			return v == o.v && n == o.n;
		}
		bool operator<(const indexStruct &o) const
		{
			return v < o.v || (v == o.v && n < o.n);
		}
	};
	std::map<indexStruct, int> indexmap;
	int indexcount;
	std::vector<Maths::Vector3> vertices;
	std::vector<unsigned int> index;
	std::vector<Maths::Vector3> normals;
	std::vector<unsigned int> normindex;
	std::vector<float> texcoord;

	VertexArray *vao;
	ElementBuffer *ebo;
	VertexBuffer *vbo;
	VertexBuffer *nbo;

  public:
	Model(const char *path);
	~Model();
	void Vertices(float *&vertices, int &n);
	void Normals(float *&normals, int &n);
	void Indices(unsigned int *&indices, int &n);
	inline void bind() { vao->bind(); }
	inline int ElementCount() { return ebo->elementCount; }
	inline void unbind() { vao->unbind(); }

  private:
	void parseVert(std::string &line, std::vector<Maths::Vector3> &list);
	void parseNormal(std::string &line, std::vector<Maths::Vector3> &list);
	void parseFaceElement(std::string &line, std::vector<Maths::Vector3> &vlist, std::vector<Maths::Vector3> &nlist);
	void insertElement(indexStruct ivn, std::vector<Maths::Vector3> &vlist, std::vector<Maths::Vector3> &nlist);
};
}; // namespace Engine