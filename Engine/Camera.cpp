#include "Camera.h"

Camera::Camera(float fov, float ar, float near, float far)
{
    projection = Maths::Matrix4::perspective(fov, ar, near, far);
    // recalculate();
}

Camera::Camera(float left, float right, float top, float bottom, float near, float far)
{
    projection = Maths::Matrix4::ortho(left, right, top, bottom, near, far);
    // recalculate();
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

void Camera::turn(int x, int y)
{
    xangle += x;
    yangle += y;
    if(yangle > 80) yangle = 80;
    if(yangle < -80) yangle = -80;
    if( xangle > 360 ) xangle = 0;
    if( xangle < 0 ) xangle = 360;

    Maths::Vector3 front = Front();
    Maths::Vector3 up = Maths::Vector3::Up - (front * Maths::Vector3::Up.dot(Front()));
    up = up/up.length();
    Maths::Vector3 side = front.cross(up);

    Maths::Quaternion q = Maths::Quaternion::fromAxisAngle(
        -xangle,
        Maths::Vector3::Up);

    Maths::Quaternion r = Maths::Quaternion::fromAxisAngle(
        yangle,
        side);

    rotation = r * q;
    recalculate();
}

void Camera::lookAt(const Maths::Vector3 &v)
{

    Maths::Vector3 dir = v - translation;
    dir = dir / dir.length();

    // float dot = dir.dot(Maths::Vector3(0, 0, -1));
    float dot = Maths::Vector3(0, 0, -1).dot(dir);
    // if (fabs(dot - -1.0f) < 0.0001f)
    // {
    //     rotation = Maths::Quaternion((float)M_PI, 0, -1, 0);
    //     recalculate();
    //     return;
    // }
    // if (fabs(dot - 1.0f) < 0.0001f)
    // {
    //     return;
    // }
    float angle = acosf(dot) * (180.0f / (float)M_PI);

    Maths::Vector3 axis = Maths::Vector3(0, 0, -1).cross(dir);
    axis = axis / axis.length();
    rotation = Maths::Quaternion::fromAxisAngle(angle, axis);
    recalculate();
}