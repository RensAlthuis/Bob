#include "SpotLight.h"

namespace Engine
{
SpotLight::SpotLight(float intensity,
                     Maths::Vector3 colour,
                     Maths::Vector3 attenuation,
                     Maths::Vector3 direction,
                     float angle,
                     float exponent)
    : intensity(intensity), colour(colour), attenuation(attenuation), direction(direction), angle(angle), exponent(exponent)
{
}

SpotLight::~SpotLight(){};

};