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

void Shader::setVec3Arr(const char* str, const Maths::Vector3 *vec, int length){
	GLuint loc = glGetUniformLocation(ID, str);
	float f[3 * length];
	for(int i = 0; i < length; i++){
		f[i*3+0] = vec[i].x;
		f[i*3+1] = vec[i].y;
		f[i*3+2] = vec[i].z;
	}
	glUniform3fv(loc, length, f);
}

void Shader::setVec4(const char *str, const Maths::Vector4 &vec)
{
	GLuint loc = glGetUniformLocation(ID, str);
	glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setVec4Arr(const char* str, const Maths::Vector4 *vec, int length){
	GLuint loc = glGetUniformLocation(ID, str);
	float f[4 * length];
	for(int i = 0; i < length; i++){
		f[i*4+0] = vec[i].x;
		f[i*4+1] = vec[i].y;
		f[i*4+2] = vec[i].z;
		f[i*4+3] = vec[i].w;
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

void Shader::setFloatArr(const char* str, const float *f, int length){
	GLuint loc = glGetUniformLocation(ID, str);
	glUniform1fv(loc, length, f);
}

void Shader::use()
{
	glUseProgram(ID);
}
Shader::~Shader()
{
}
};