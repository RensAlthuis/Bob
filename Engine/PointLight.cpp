#include "PointLight.h"

namespace Engine
{
PointLight::PointLight(float intensity, Maths::Vector3 colour, Maths::Vector3 attenuation)
    : Object(), intensity(intensity), colour(colour), attenuation(attenuation)
{
}

PointLight::~PointLight()
{
}

} // namespace Engine