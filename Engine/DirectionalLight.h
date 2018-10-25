#pragma once
#include "Object.h"
#include "Maths/Maths.h"

namespace Engine
{
class DirectionalLight : public Object
{

  public:
    float intensity;
    Maths::Vector3 colour;

  public:
    DirectionalLight(float intensity, Maths::Vector3 colour);
    ~DirectionalLight();
};
}; // namespace Engine