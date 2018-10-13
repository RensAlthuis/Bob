#include "Shader.h"


namespace Engine{
Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
	int success;
	char infoLog[512];
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	char *vertexShaderSource;
	long len;
	FileReader::readFile(vertexPath, vertexShaderSource, len);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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
	char *fragmentShaderSource;
	FileReader::readFile(fragmentPath, fragmentShaderSource, len);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
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
void Shader::setVec4(const char *str, const Maths::Vector4 &vec)
{
	GLuint loc = glGetUniformLocation(ID, str);
	glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}
void Shader::setInt1(const char *str, int i)
{
	glUniform1i(glGetUniformLocation(ID, str), i);
}

void Shader::setFloat1(const char *str, float f)
{
	glUniform1f(glGetUniformLocation(ID, str), f);
}

void Shader::use()
{
	glUseProgram(ID);
}
Shader::~Shader()
{
}
};