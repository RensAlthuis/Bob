#include "Camera.h"

namespace Engine
{
Camera::Camera(float fov, float ar, float near, float far) : yangle(0), xangle(0)
{
    projection = Maths::Matrix4::perspective(fov, ar, near, far);
}

Camera::Camera(float left, float right, float top, float bottom, float near, float far) : yangle(0), xangle(0)
{
    projection = Maths::Matrix4::ortho(left, right, top, bottom, near, far);
}

Transform& Camera::getTransform() 
{
    return transform;
}

Camera::~Camera()
{}

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
    transform.rotation = tilt * swing;
}

}; // namespace Engine
