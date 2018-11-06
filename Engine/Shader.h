#pragma once

#include <glad/glad.h>
#include "Maths/Maths.h"
#include <string>
#include <sstream>
#include "FileReader.h"
#include <assert.h>

namespace Engine
{
class Shader
{
public:
private:
	GLuint ID;
	int nDirLights;
	int nPointLights;
	int nSpotLights;

private:
	long parseFile(const char *path, std::ostringstream& target);
	void insertLights(std::ostringstream& shader);
	void handleMacro(std::ostringstream& shader, const char *macro, std::istringstream& file);

public:
	Shader(const char *vertexPath, const char *fragmentPath, int nDirLights, int nPointLights, int nSpotLights);
	void setMat4(const char *str, const Maths::Matrix4 &mat) const;
	void setVec2(const char *str, const Maths::Vector2 &vec) const;
	void setVec3(const char *str, const Maths::Vector3 &vec) const;
	void setVec3Arr(const char *str, const Maths::Vector3 *vec, int length) const;
	void setVec4(const char *str, const Maths::Vector4 &vec) const;
	void setVec4Arr(const char *str, const Maths::Vector4 *vec, int length) const;
	void setInt1(const char *str, int i) const;
	void setFloat(const char *str, float f) const;
	void setFloatArr(const char *str, const float *f, int length) const;
	void setLights(int nDirLights, int nPointLights, int nSpotLights) const;
	void use() const;
	~Shader();
};

}; // namespace Engine