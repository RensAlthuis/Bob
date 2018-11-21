#include "Model.h"

namespace Engine
{
Model::Model(const char *path)
{
	char *file;
	long len;
	FileReader::readFile(path, file, len);
	std::istringstream f = std::istringstream(file);
	std::vector<std::string *> lines;
	char buf[256];
	while (!f.eof())
	{
		f.getline(buf, 256);
		lines.push_back(new std::string(buf));
	}

	//assuming the values are placed in order! verts -> normals -> faces
	//otherwise likely a silent error
	std::vector<Maths::Vector3> vlist;
	std::vector<Maths::Vector3> nlist;
	std::map<indexStruct, int> indexmap;
	for (auto line : lines)
	{
		if ((*line)[0] == '#')
		{
			continue;
		}
		else if ((*line)[0] == 'v' && (*line)[1] == ' ')
		{
			parseVert(*line, vlist);
		}
		else if ((*line)[0] == 'v' && (*line)[1] == 'n' && (*line)[2] == ' ')
		{
			parseNormal(*line, nlist);
		}
		else if ((*line)[0] == 'f' && (*line)[1] == ' ')
		{
			parseFaceElement(indexmap, *line, vlist, nlist);
		}
	}

	vao = new VertexArray();

	//set up vertices
	float *fverts = new float[vertices.size() * 3];
	Vertices(fverts);
	auto vbo = new VertexBuffer(fverts, vertices.size(), 3);
	delete[] fverts;
	vao->addBuffer(vbo, 0);

	//set up normals
	float *fnormals = new float[normals.size() * 3];
	Normals(fnormals);
	auto nbo = new VertexBuffer(fnormals, normals.size(), 3);
	delete[] fnormals;
	vao->addBuffer(nbo, 1);

	//set up indices
	auto ebo = new ElementBuffer(index.data(), index.size());
	vao->setEBO(ebo);

	vertices.clear();
	normals.clear();
	index.clear();
}

void Model::parseVert(std::string &line, std::vector<Maths::Vector3> &list)
{
	float x, y, z;
	sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
	list.push_back(Maths::Vector3(x, y, z));
}

void Model::parseNormal(std::string &line, std::vector<Maths::Vector3> &list)
{
	float x, y, z;
	sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
	list.push_back(Maths::Vector3(x, y, z));
}

void Model::parseFaceElement(std::map<indexStruct, int> &indexmap, std::string &line, std::vector<Maths::Vector3> &vlist, std::vector<Maths::Vector3> &nlist)
{
	int a, b, c, d, e, f;
	sscanf(line.c_str(), "f %u//%u %u//%u %u//%u", &a, &b, &c, &d, &e, &f);
	indexStruct ivn1{a - 1, b - 1};
	indexStruct ivn2{c - 1, d - 1};
	indexStruct ivn3{e - 1, f - 1};
	insertElement(indexmap, ivn1, vlist, nlist);
	insertElement(indexmap, ivn2, vlist, nlist);
	insertElement(indexmap, ivn3, vlist, nlist);
}

void Model::insertElement(std::map<indexStruct, int> &indexmap, indexStruct ivn, std::vector<Maths::Vector3> &vlist, std::vector<Maths::Vector3> &nlist)
{
	//check if map already has key
	if (indexmap.count(ivn) == 0)
	{
		//map doesn't have key -> add key to map, push vertex and normal on indexcount positions in their respective C-Vertexes
		int count = indexmap.size();
		indexmap.insert(std::pair<indexStruct, int>(ivn, count));
		index.push_back(count);
		vertices.push_back(vlist[ivn.v]);
		normals.push_back(nlist[ivn.n]);
	}
	else
	{
		index.push_back(indexmap.at(ivn));
	}
}

void Model::Vertices(float *array)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		array[i * 3 + 0] = vertices[i].x;
		array[i * 3 + 1] = vertices[i].y;
		array[i * 3 + 2] = vertices[i].z;
	}
}

void Model::Normals(float *array)
{
	for (int i = 0; i < normals.size(); i++)
	{
		array[i * 3 + 0] = normals[i].x;
		array[i * 3 + 1] = normals[i].y;
		array[i * 3 + 2] = normals[i].z;
	}
}

Model::~Model()
{
	delete vao;
}
}; // namespace Engine