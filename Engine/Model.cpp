#include "Model.h"

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

	for (auto line : lines)
	{
		if ((*line)[0] == '#')
		{
			continue;
		}
		else if ((*line)[0] == 'v' && (*line)[1] == ' ')
		{
			parseVert(*line);
		}
		else if ((*line)[0] == 'v' && (*line)[1] == 'n' && (*line)[2] == ' ')
		{
			parseNormal(*line);
		}
		else if ((*line)[0] == 'f' && (*line)[1] == ' ')
		{
			parseFaceElement(*line);
		}
	}

	for (int i = 0; i < lines.size(); i++)
	{
		delete lines[i];
	}
	delete file;

	int nverts, nnorms, nindices;
	float *verts;
	float *normals;
	unsigned int *indices;
	Vertices(verts, nverts);
	Indices(indices, nindices);
	Normals(normals, nnorms);
	ebo = new ElementBuffer(indices, nindices);
	VertexBuffer *vbo = new VertexBuffer(verts, nverts, 3);
	VertexBuffer *nbo = new VertexBuffer(normals, nnorms, 3);
	vao = new VertexArray();
	vao->setEBO(ebo);
	vao->addBuffer(vbo, 0);
	vao->addBuffer(nbo, 1);
}

void Model::parseVert(std::string &line)
{
	float x, y, z;
	sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
	verts.push_back(x);
	verts.push_back(y);
	verts.push_back(z);
}

void Model::parseNormal(std::string &line)
{
	float x, y, z;
	sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
	normal.push_back(Maths::Vector3(x, y ,z));
}

void Model::parseFaceElement(std::string &line)
{
	int a, b, c, d, e, f;
	sscanf(line.c_str(), "f %u//%u %u//%u %u//%u", &a, &b, &c, &d, &e, &f);
	index.push_back(a - 1);
	index.push_back(c - 1);
	index.push_back(e - 1);
	normindex.push_back(b - 1);
	normindex.push_back(d - 1);
	normindex.push_back(f - 1);
}

void Model::Vertices(float *&vertices, int &n)
{
	vertices = verts.data();
	n = verts.size() / 3;
}

void Model::Normals(float *&normals, int &n)
{
	float *f = new float[normindex.size()*3];
	for (int i = 0; i < normindex.size(); i++)
	{
		f[i*3+0] = normal[normindex[i]].x;
		f[i*3+1] = normal[normindex[i]].y;
		f[i*3+2] = normal[normindex[i]].z;
	}
	normals = f;
	n = normindex.size();
	for(int i = 0; i < normindex.size(); i++){
		std::cout << i << ": " << normals[i*3] << ", " << normals[i*3+1] << ", " << normals[i*3+2] << ", " << normal[normindex[i]]<< std::endl;
	}
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
void Model::unbind(){
	vao->unbind();
}

Model::~Model()
{
}