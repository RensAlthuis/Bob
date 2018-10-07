#include "Model.h"

namespace Engine{
Model::Model(const char *path) : indexmap(),
								 indexcount(0)
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
			parseFaceElement(*line, vlist, nlist);
		}
	}

	int nverts, nnorms, nindices;
	float *fverts;
	float *fnormals;
	unsigned int *uiindices;
	Vertices(fverts, nverts);
	Indices(uiindices, nindices);
	Normals(fnormals, nnorms);
	ebo = new ElementBuffer(uiindices, nindices);
	VertexBuffer *vbo = new VertexBuffer(fverts, nverts, 3);
	VertexBuffer *nbo = new VertexBuffer(fnormals, nnorms, 3);
	vao = new VertexArray();
	vao->setEBO(ebo);
	vao->addBuffer(vbo, 0);
	vao->addBuffer(nbo, 1);
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

void Model::parseFaceElement(std::string &line, std::vector<Maths::Vector3> &vlist, std::vector<Maths::Vector3> &nlist)
{
	int a, b, c, d, e, f;
	sscanf(line.c_str(), "f %u//%u %u//%u %u//%u", &a, &b, &c, &d, &e, &f);
	indexStruct ivn1{a - 1, b - 1};
	indexStruct ivn2{c - 1, d - 1};
	indexStruct ivn3{e - 1, f - 1};
	insertElement(ivn1, vlist, nlist);
	insertElement(ivn2, vlist, nlist);
	insertElement(ivn3, vlist, nlist);
}

void Model::insertElement(indexStruct ivn, std::vector<Maths::Vector3> &vlist, std::vector<Maths::Vector3> &nlist)
{
	//check if map already has key
	if (indexmap.count(ivn) == 0)
	{
		//map doesn't have key -> add key to map, push vertex and normal on indexcount positions in their respective C-Vertexes
		indexmap.insert(std::pair<indexStruct, int>(ivn, indexcount));
		index.push_back(indexcount);
		indexcount++;
		vertices.push_back(vlist[ivn.v]);
		normals.push_back(nlist[ivn.n]);
	}
	else
	{
		index.push_back(indexmap.at(ivn));
	}
}

void Model::Vertices(float *&array, int &n)
{
	float *f = new float[vertices.size() * 3];
	for (int i = 0; i < vertices.size(); i++)
	{
		f[i * 3 + 0] = vertices[i].x;
		f[i * 3 + 1] = vertices[i].y;
		f[i * 3 + 2] = vertices[i].z;
	}
	array = f;
	n = vertices.size();
}

void Model::Normals(float *&array, int &n)
{
	float *f = new float[normals.size() * 3];
	for (int i = 0; i < normals.size(); i++)
	{
		f[i * 3 + 0] = normals[i].x;
		f[i * 3 + 1] = normals[i].y;
		f[i * 3 + 2] = normals[i].z;
	}
	array = f;
	n = normals.size();
}

void Model::Indices(unsigned int *&indices, int &n)
{
	indices = index.data();
	n = index.size();
}

void Model::bind()
{
	vao->bind();
}
int Model::ElementCount()
{
	return ebo->elementCount;
}
void Model::unbind()
{
	vao->unbind();
}

Model::~Model()
{
}
};