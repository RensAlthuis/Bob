#include "PointLight.h"

namespace Engine
{
PointLight::PointLight(float intensity, Maths::Vector3 colour, Maths::Vector3 attenuation)
    : Object(), intensity(intensity), colour(colour), attenuation(attenuation)
{
}

void PointLight::setShader(Shader *shader, const Camera &cam, int index)
{
    char num[10];
    sprintf(num, "[%d]", index);

    char string[256];
    memset(string, 0, 256);
    strcpy(string, "pointLightPos");
    strcat(string, num);
    shader->setVec3(string, (translation + (parent != nullptr? parent->translation : Maths::Vector3::Zero))*cam.Transform());

    strcpy(string, "pointLightIntensity");
    strcat(string, num);
    shader->setFloat(string, intensity);

    strcpy(string, "pointLightColour");
    strcat(string, num);
    shader->setVec3(string, colour);

    strcpy(string, "pointLightAttenuation");
    strcat(string, num);
    shader->setVec3(string, attenuation);
}

PointLight::~PointLight()
{
}

} // namespace Engine