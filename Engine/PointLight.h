#pragma once
#include "Object.h"
#include "Maths/Maths.h"
#include "Shader.h"
#include "Camera.h"

namespace Engine
{
class PointLight : public Object
{
public:
  float intensity;
  Maths::Vector3 colour;
  Maths::Vector3 attenuation;

public:
  PointLight(float intensity, Maths::Vector3 colour, Maths::Vector3 attenuation);
  void setShader(Shader *shader, Camera &cam, int index);
  ~PointLight();
};
}; // namespace Engine