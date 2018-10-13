#pragma once
#include "Object.h"
#include <iostream>
namespace Engine{
class Camera : public Object
{

  private:
    Maths::Matrix4 projection;
    float xangle;
    float yangle;

  public:
    Camera(float fov, float ar, float near, float far);
    Camera(float left, float right, float top, float bottom, float near, float far);
    ~Camera();
    const Maths::Matrix4 &Projection();
    void turn(float x, float y);

  private:
    void recalculate() override;
};
};