#include "Shader.h"

namespace Engine
{
Shader::Shader(const char *vertexPath, const char *fragmentPath, int nDirLights, int nPointLights, int nSpotLights)
	: nDirLights(nDirLights), nPointLights(nPointLights), nSpotLights(nSpotLights)
{
	int success;
	char infoLog[512];
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::ostringstream vertexShaderSource;
	long len = parseFile(vertexPath, vertexShaderSource);
	char *vsource = new char[len];
	strcpy(vsource, vertexShaderSource.str().c_str());
	glShaderSource(vertexShader, 1, &vsource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR: failed to compile vertex shader\n"
				  << infoLog << std::endl;
	}

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::ostringstream fragmentShaderSource;
	len = parseFile(fragmentPath, fragmentShaderSource);
	char *fsource = new char[len];
	strcpy(fsource, fragmentShaderSource.str().c_str());
	glShaderSource(fragmentShader, 1, &fsource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR: failed to compile fragment shader\n"
				  << infoLog << std::endl;
	}

	//creating shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR: failed to link shader program\n"
				  << infoLog << std::endl;
	}
	//linked shaders can be deleted
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::setMat4(const char *str, const Maths::Matrix4 &mat)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, str), 1, false, mat.mat);
}

void Shader::setVec2(const char *str, const Maths::Vector2 &vec)
{
	glUniform2f(glGetUniformLocation(ID, str), vec.x, vec.y);
}

void Shader::setVec3(const char *str, const Maths::Vector3 &vec)
{
	glUniform3f(glGetUniformLocation(ID, str), vec.x, vec.y, vec.z);
}

void Shader::setVec3Arr(const char *str, const Maths::Vector3 *vec, int length)
{
	GLuint loc = glGetUniformLocation(ID, str);
	float f[3 * length];
	for (int i = 0; i < length; i++)
	{
		f[i * 3 + 0] = vec[i].x;
		f[i * 3 + 1] = vec[i].y;
		f[i * 3 + 2] = vec[i].z;
	}
	glUniform3fv(loc, length, f);
}

void Shader::setVec4(const char *str, const Maths::Vector4 &vec)
{
	GLuint loc = glGetUniformLocation(ID, str);
	glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setVec4Arr(const char *str, const Maths::Vector4 *vec, int length)
{
	GLuint loc = glGetUniformLocation(ID, str);
	float f[4 * length];
	for (int i = 0; i < length; i++)
	{
		f[i * 4 + 0] = vec[i].x;
		f[i * 4 + 1] = vec[i].y;
		f[i * 4 + 2] = vec[i].z;
		f[i * 4 + 3] = vec[i].w;
	}
	glUniform4fv(loc, length, f);
}

void Shader::setInt1(const char *str, int i)
{
	glUniform1i(glGetUniformLocation(ID, str), i);
}

void Shader::setFloat(const char *str, float f)
{
	glUniform1f(glGetUniformLocation(ID, str), f);
}

void Shader::setFloatArr(const char *str, const float *f, int length)
{
	GLuint loc = glGetUniformLocation(ID, str);
	glUniform1fv(loc, length, f);
}

void Shader::use()
{
	glUseProgram(ID);
}

long Shader::parseFile(const char *path, std::ostringstream &target)
{
	char *file;
	long len;
	FileReader::readFile(path, file, len);
	std::istringstream stream(file);
	std::string line;
	while (std::getline(stream, line))
	{
		char *tag = new char[64];
		if (sscanf(line.c_str(), "#macro %s", tag) == 1)
		{
			handleMacro(target, tag, stream);
		}
	}
	return target.str().size();
}

uint64_t constexpr mix(char m, uint64_t s)
{
	return ((s << 7) + ~(s >> 3)) + ~m;
}

uint64_t constexpr hash(const char *m)
{
	return (*m) ? mix(*m, hash(m + 1)) : 0;
}

void Shader::handleMacro(std::ostringstream &shader, const char *macro, std::istringstream &file)
{
	switch (hash(macro))
	{
	case hash("INSERTVERSION"):
		shader << "#version 330 core" << std::endl;
		break;
	case hash("USE_LIGHTS"):
		insertLights(shader);
		break;
	case hash("CODE"):
		std::string line;
		while (std::getline(file, line))
		{
			shader << line << std::endl;
		}
		break;
	}
}

void Shader::insertLights(std::ostringstream &shader)
{
	if (nDirLights > 0)
	{
		shader << "#define nDirLights " << nDirLights << std::endl;
		shader << "uniform vec3 dirLightPos[nDirLights];\n"
			   << "uniform float dirLightIntensity[nDirLights];\n"
			   << "uniform vec3 dirLightColour[nDirLights];\n"
			   << std::endl;
	}

	if (nPointLights > 0)
	{
		shader << "#define nPointLights " << nPointLights << std::endl;
		shader << "uniform vec3 pointLightPos[nPointLights];\n"
			   << "uniform vec3 pointLightAttenuation[nPointLights];\n"
			   << "uniform float pointLightIntensity[nPointLights];\n"
			   << "uniform vec3 pointLightColour[nPointLights];\n"
			   << std::endl;
	}

	if (nSpotLights > 0)
	{
		shader << "#define nSpotLights " << nSpotLights << std::endl;
		shader << "uniform vec3 spotLightPos[nSpotLights];\n"
			   << "uniform float spotLightIntensity[nSpotLights];\n"
			   << "uniform vec3 spotLightAttenuation[nSpotLights];\n"
			   << "uniform vec3 spotLightDir[nSpotLights];\n"
			   << "uniform float spotLightAngle[nSpotLights];\n"
			   << "uniform float spotLightExponent[nSpotLights];\n"
			   << "uniform vec3 spotLightColour[nSpotLights];\n"
			   << std::endl;
	}
}

Shader::~Shader()
{
}
}; // namespace Engine