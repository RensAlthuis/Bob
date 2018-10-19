#pragma once

#include <glad/glad.h>
#include "Maths/Maths.h"
#include "FileReader.h"

namespace Engine{
class Shader
{
  public:
  private:
	GLuint ID;

  public:
	Shader(const char *vertexPath, const char *fragmentPath);
	void setMat4(const char *str, const Maths::Matrix4 &mat);
	void setVec2(const char *str, const Maths::Vector2 &vec);
	void setVec3(const char *str, const Maths::Vector3 &vec);
	void setVec3Arr(const char* str, const Maths::Vector3 *vec, int length);
	void setVec4(const char *str, const Maths::Vector4 &vec);
	void setVec4Arr(const char* str, const Maths::Vector4 *vec, int length);
	void setInt1(const char *str, int i);
	void setFloat(const char *str, float f);
	void setFloatArr(const char* str, const float *f, int length);
	void use();
	~Shader();
};

};