#pragma once
#include "Object.h"
#include "Maths/Maths.h"
#include "Shader.h"
#include "Camera.h"

namespace Engine
{
class DirectionalLight : public Object
{

public:
  float intensity;
  Maths::Vector3 colour;

public:
  DirectionalLight(float intensity, Maths::Vector3 colour);
  void setShader(Shader *shader, const Camera &cam, int index);
  ~DirectionalLight();
};
}; // namespace Engine