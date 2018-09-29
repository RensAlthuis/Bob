#include "Camera.h"

Camera::Camera(float fov, float ar, float near, float far) : pos(0, 0, 3.0f)
{
    rotX = 0;
    rotY = 0;
    projection = Maths::Matrix4::perspective(fov, ar, near, far);
    recalculate();
}

Camera::Camera(float left, float right, float top, float bottom, float near, float far) : pos(0, 0, 0)
{
    rotX = 0;
    rotY = 0;
    projection = Maths::Matrix4::ortho(left, right, top, bottom, near, far);
    recalculate();
}

Camera::~Camera()
{
}

void Camera::recalculate()
{
    float angle = rotX * ((float)M_PI / 180.0f);
    float xangle = cosf(angle);
    float zangle = sinf(angle);
    transform = Maths::Matrix4::rotate(rotX, 0, 1, 0) * Maths::Matrix4::rotate(-rotY, xangle, 0, zangle) * Maths::Matrix4::translate(-pos.x, -pos.y, -pos.z);
}

const Maths::Matrix4 &Camera::Transform()
{
    return transform;
}

const Maths::Vector3 Camera::Front()
{
    Maths::Vector3 front(0, 0, 1.0f);
    front = Maths::Matrix4::rotate(-rotX, 0, 1, 0 ) * front;
    front = front / front.length();
    return front;
}
const Maths::Matrix4 &Camera::Projection()
{
    return projection;
}

void Camera::move(float forward, float up, float right)
{
    Maths::Vector3 front = Front();
    pos = pos + (front * -forward) + (front.cross(Maths::Vector3::Up) * -right);
    pos.y += up;
    recalculate();
}

void Camera::rotate(int x, int y)
{
    rotX += x;
    rotY += y;
    while (rotX >= 360)
        rotX -= 360;
    while (rotX < 0)
        rotX += 360;
    if (rotY > 90)
        rotY = 90;
    while (rotY < -90)
        rotY = -90;
    recalculate();
}