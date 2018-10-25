#pragma once
#include "Object.h"
#include "Maths/Maths.h"

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
  ~PointLight();
};
}; // namespace Engine