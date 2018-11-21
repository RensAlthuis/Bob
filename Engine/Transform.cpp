#include "Transform.h"

namespace Engine
{
Transform::Transform() : translation(0, 0, 0),
                         scaling(1, 1, 1),
                         rotation(1, 0, 0, 0),
                         dirty(true)
{
    recalculate();
}
void Transform::recalculate()
{
    transform = Maths::Matrix4::scale(scaling.x, scaling.y, scaling.z) *
                Maths::Matrix4::rotate(rotation) *
                Maths::Matrix4::translate(translation);
    dirty = false;
}

void Transform::translate(Maths::Vector3 v, bool inWorldSpace)
{
    if (inWorldSpace)
    {
        translation = translation + v;
    }
    else
    {
        Maths::Vector3 v2 = v.rotate(rotation);
        translation = translation + v2;
    }
    dirty = true;
}

void Transform::rotate(Maths::Quaternion q)
{
    rotation = q * rotation;
    dirty = true;
}

void Transform::lookAt(const Maths::Vector3 &v)
{

    Maths::Vector3 dir = (v - translation).normalize();
    float anglefront = atan2f(Maths::Vector3::Forward.x, Maths::Vector3::Forward.z);
    float angledir = atan2f(dir.x, dir.z);

    float xangle = (anglefront - angledir) * (180.0f / (float)M_PI);
    float a = acosf(dir.dot(Maths::Vector3::Up));
    float yangle = ((float)M_PI_2 - a) * (180.0f / (float)M_PI);

    Maths::Quaternion swing(Maths::Quaternion::fromAxisAngle(-xangle, Maths::Vector3::Up));
    Maths::Quaternion tilt(Maths::Quaternion::fromAxisAngle(yangle,
                                                            Maths::Vector3::Right.rotate(swing)));

    rotation = tilt * swing;
    dirty = true;
}

void Transform::scale(Maths::Vector3 s, bool set)
{
    if (set)
    {
        scaling = s;
    }
    else
    {
        scaling = scaling + s;
    }
    dirty = true;
}

} // namespace Engine