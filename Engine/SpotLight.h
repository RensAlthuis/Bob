#pragma once
#include "Object.h"
#include "Maths/Maths.h"

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
    ~SpotLight();
};
}; // namespace Engine