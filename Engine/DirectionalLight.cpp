#include "DirectionalLight.h"
namespace Engine 
{

DirectionalLight::DirectionalLight(float intensity, Maths::Vector3 colour)
: intensity(intensity), colour(colour)
{
}

DirectionalLight::~DirectionalLight(){}
};