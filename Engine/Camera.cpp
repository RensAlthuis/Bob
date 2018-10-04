#include "Camera.h"

Camera::Camera(float fov, float ar, float near, float far) : yangle(0), xangle(0)
{
    projection = Maths::Matrix4::perspective(fov, ar, near, far);
    recalculate();
}

Camera::Camera(float left, float right, float top, float bottom, float near, float far) : yangle(0), xangle(0)
{
    projection = Maths::Matrix4::ortho(left, right, top, bottom, near, far);
    recalculate();
}

void Camera::recalculate()
{
    transform = Maths::Matrix4::scale(scale, scale, scale) *
                Maths::Matrix4::rotate(rotation.inverse()) *
                Maths::Matrix4::translate(translation * -1);
}

Camera::~Camera()
{
}

const Maths::Matrix4 &Camera::Projection()
{
    return projection;
}

void Camera::turn(float x, float y)
{

    xangle += x;
    yangle += y;
    if (xangle >= 360)
        xangle -= 360;
    if (yangle >= 360)
        yangle -= 360;
    if (xangle < 0)
        xangle += 360;
    if (yangle < 0)
        yangle += 360;

    Maths::Quaternion swing(Maths::Quaternion::fromAxisAngle(-xangle, Maths::Vector3::Up));
    Maths::Vector3 side = Maths::Vector3::Right.rotate(swing);
    Maths::Quaternion tilt(Maths::Quaternion::fromAxisAngle(yangle, side));
    rotation = tilt * swing;
    recalculate();
}

void Camera::lookAt(const Maths::Vector3 &v)
{

    Maths::Vector3 dir = (v - translation).normalize();
    float anglefront = atan2f(Maths::Vector3::Forward.x, Maths::Vector3::Forward.z);
    float angledir = atan2f(dir.x, dir.z);
    xangle = (anglefront - angledir) * (180.0f / (float)M_PI);
    float a = acosf(dir.dot(Maths::Vector3::Up));
    yangle = ((float)M_PI_2 - a) * (180.0f / (float)M_PI);
    Maths::Quaternion swing(Maths::Quaternion::fromAxisAngle(-xangle, Maths::Vector3::Up));
    Maths::Vector3 side = Maths::Vector3::Right.rotate(swing);
    Maths::Quaternion tilt(Maths::Quaternion::fromAxisAngle(yangle, side));
    rotation = tilt*swing;
    recalculate();
}