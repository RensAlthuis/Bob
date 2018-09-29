#pragma once
#include "FileReader.h"
#include <sstream>
#include <iostream>
#include <vector>
#include "Maths/Maths.h"

class Model
{
  private:
	std::vector<float> verts;
	std::vector<unsigned int> index;
	std::vector<float> normal;
	std::vector<unsigned int> normindex;
	std::vector<float> texcoord;

  public:
	Model(const char *path);
	~Model();
	void Vertices(float *&vertices, int &n);
	void Normals(float *&normals, int &n);
	void Indices(unsigned int *&indices, int &n);

  private:
	void parseVert(std::string &line);
	void parseNormal(std::string &line);
	void parseFaceElement(std::string &line);
};