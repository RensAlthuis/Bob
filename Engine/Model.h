#pragma once
#include "FileReader.h"
#include <memory>
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

	std::vector<Maths::Vector3> vertices;
	std::vector<unsigned int> index;
	std::vector<Maths::Vector3> normals;
	// std::vector<float> texcoord;

	std::unique_ptr<VertexArray> vao;

  public:
	Model(const char *path);
	~Model();
	void Vertices(std::unique_ptr<float[]> &vertices);
	void Normals(std::unique_ptr<float[]> &normals);
	void Indices(std::unique_ptr<unsigned int[]> &indices);
	inline void bind() { vao->bind(); }
	inline int ElementCount() { return vao->ElementCount(); }
	inline void unbind() { vao->unbind(); }

  private:
	void parseVert(std::string &line, std::vector<Maths::Vector3> &list);
	void parseNormal(std::string &line, std::vector<Maths::Vector3> &list);
	void parseFaceElement(std::map<indexStruct, int>& indexmap, std::string &line, std::vector<Maths::Vector3> &vlist, std::vector<Maths::Vector3> &nlist);
	void insertElement(std::map<indexStruct, int>& indexmap, indexStruct ivn, std::vector<Maths::Vector3> &vlist, std::vector<Maths::Vector3> &nlist);
};
}; // namespace Engine