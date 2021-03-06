#pragma once
#include "Object.h"
#include "Maths/Maths.h"
#include "Shader.h"
#include "Camera.h"

namespace Engine
{
class SpotLight : public Object
{
public:
  float intensity;
  Maths::Vector3 colour;
  Maths::Vector3 attenuation;
  Maths::Vector3 direction;
  float angle;
  float exponent;

public:
  SpotLight(float intensity,
            Maths::Vector3 colour,
            Maths::Vector3 attenuation,
            Maths::Vector3 direction,
            float angle,
            float exponent);
  void setShader(Shader *shader, const Camera &cam, int index);
  ~SpotLight();
};
}; // namespace Engine