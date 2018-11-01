#include "DirectionalLight.h"
namespace Engine
{

DirectionalLight::DirectionalLight(float intensity, Maths::Vector3 colour)
    : intensity(intensity), colour(colour)
{
}

void DirectionalLight::setShader(Shader *shader, const Camera &cam, int index)
{

    char num[10];
    sprintf(num, "[%d]", index);

    char string[256];
    memset(string, 0, 256);
    strcpy(string, "dirLightPos");
    strcat(string, num);
    shader->setVec3(string, (translation + (parent != nullptr? parent->translation : Maths::Vector3::Zero)).normalize());

    strcpy(string, "dirLightIntensity");
    strcat(string, num);
    shader->setFloat(string, intensity);

    strcpy(string, "dirLightColour");
    strcat(string, num);
    shader->setVec3(string, colour);
}

DirectionalLight::~DirectionalLight() {}
}; // namespace Engine