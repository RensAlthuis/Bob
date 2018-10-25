#include "Camera.h"

namespace Engine{
Camera::Camera(float fov, float ar, float near, float far) : Object(), yangle(0), xangle(0)
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
    transform = Maths::Matrix4::scale(scaling.x, scaling.y, scaling.z) *
                Maths::Matrix4::rotate(rotation.inverse()) *
                Maths::Matrix4::translate(translation * -1) *
                (parent == nullptr? Maths::Matrix4::identity() : parent->Transform());
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

};
