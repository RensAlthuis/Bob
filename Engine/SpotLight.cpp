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

void SpotLight::setShader(Shader *shader, Camera &cam, int index)
{
    char num[10];
    sprintf(num, "[%d]", index);

    char string[256];
    memset(string, 0, 256);
    strcpy(string, "spotLightPos");
    strcat(string, num);
    const Maths::Vector3 pos = cam.getTransform().translation;
    shader->setVec3(string, (translation + (parent != nullptr ? parent->translation : Maths::Vector3::Zero)) - pos);

    memset(string, 0, 256);
    strcpy(string, "spotLightIntensity");
    strcat(string, num);
    shader->setFloat(string, intensity);

    memset(string, 0, 256);
    strcpy(string, "spotLightColour");
    strcat(string, num);
    shader->setVec3(string, colour);

    memset(string, 0, 256);
    strcpy(string, "spotLightAttenuation");
    strcat(string, num);
    shader->setVec3(string, attenuation);

    memset(string, 0, 256);
    strcpy(string, "spotLightDir");
    strcat(string, num);
    const Maths::Quaternion rot = cam.getTransform().rotation;
    shader->setVec3(string, -Front().rotate(rot.inverse()));

    memset(string, 0, 256);
    strcpy(string, "spotLightAngle");
    strcat(string, num);
    shader->setFloat(string, angle);

    memset(string, 0, 256);
    strcpy(string, "spotLightExponent");
    strcat(string, num);
    shader->setFloat(string, exponent);
}

SpotLight::~SpotLight(){};

}; // namespace Engine