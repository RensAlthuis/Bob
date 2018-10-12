#include "Object.h"

Object::Object() : translation(0, 0, 0),
                   scale(1),
                   rotation(1, 0, 0, 0)
{
    transform = Maths::Matrix4::identity();
    recalculate();
}

Object::~Object()
{
}

void Object::recalculate()
{
    transform = Maths::Matrix4::translate(translation) *
                Maths::Matrix4::rotateAxisAngle(0, 1, 0, 0) *
                scale;
}

const Maths::Matrix4 &Object::Transform() const
{
    return transform;
}

const Maths::Vector3 Object::Front() const
{
    return Maths::Vector3::Forward.rotate(rotation).normalize();
}

void Object::translate(Maths::Vector3 v, bool inWorldSpace)
{
    if (inWorldSpace)
    {
        Maths::Vector3 v2 = v.rotate(rotation);
        translation.x += v2.x;
        translation.y += v2.y;
        translation.z += v2.z;
    }
    else
    {
        translation = translation + v;
    }
    recalculate();
}

void Object::translate(float x, float y, float z, bool inWorldSpace)
{
    translate(Maths::Vector3(x, y, z), inWorldSpace);
}

void Object::rotate(Maths::Quaternion q)
{
    rotation = q * rotation;
    recalculate();
}

void Object::lookAt(const Maths::Vector3 &v)
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

    rotation = tilt*swing;
    recalculate();
}