#pragma once
#include "FileReader.h"
#include <sstream>
#include <iostream>
#include <vector>
#include "Maths/Maths.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"

class Model
{
  private:
	std::vector<float> verts;
	std::vector<unsigned int> index;
	std::vector<Maths::Vector3> normal;
	std::vector<unsigned int> normindex;
	std::vector<float> texcoord;

	VertexArray *vao;
	ElementBuffer *ebo;

  public:
	Model(const char *path);
	~Model();
	void Vertices(float *&vertices, int &n);
	void Normals(float *&normals, int &n);
	void Indices(unsigned int *&indices, int &n);
	void bind();
	void unbind();
	int ElementCount();
  private:
	void parseVert(std::string &line);
	void parseNormal(std::string &line);
	void parseFaceElement(std::string &line);
};