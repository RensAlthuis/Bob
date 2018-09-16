#pragma once

#include <glad/glad.h>
#include "Maths/maths.h"
#include "FileReader.h"

class Shader
{
public:

private:
	GLuint ID;
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void setMat4(const char* str, const Maths::Matrix4& mat);
	void setVec2(const char* str, const Maths::Vector2& vec);
	void setVec3(const char* str, const Maths::Vector3& vec);
	void setVec4(const char* str, const Maths::Vector4& vec);
	void setInt1(const char* str, int i);
	void use();
	~Shader();
};

