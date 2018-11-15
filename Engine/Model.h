#pragma once
#include "FileReader.h"
#include <memory>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include "Maths/Maths.h"
#include "Buffer/VertexBuffer.h"
#include "Buffer/ElementBuffer.h"
#include "Buffer/VertexArray.h"

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

	std::vector<Maths::Vector3> vertices;
	std::vector<unsigned int> index;
	std::vector<Maths::Vector3> normals;

	VertexArray* vao;

  public:
	Model(const char *path);
	~Model();
	inline void bind() { vao->bind(); }
	inline int ElementCount() { return vao->ElementCount(); }
	inline void unbind() { vao->unbind(); }

  private:
	void Vertices(float *vertices);
	void Normals(float *normals);
	void Indices(unsigned int *indices);
	void parseVert(std::string &line, std::vector<Maths::Vector3> &list);
	void parseNormal(std::string &line, std::vector<Maths::Vector3> &list);
	void parseFaceElement(std::map<indexStruct, int>& indexmap, std::string &line, std::vector<Maths::Vector3> &vlist, std::vector<Maths::Vector3> &nlist);
	void insertElement(std::map<indexStruct, int>& indexmap, indexStruct ivn, std::vector<Maths::Vector3> &vlist, std::vector<Maths::Vector3> &nlist);
};
}; // namespace Engine