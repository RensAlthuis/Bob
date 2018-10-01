#pragma once
#include "Object.h"
#include <iostream>

class Camera : public Object
{

  private:
    Maths::Matrix4 projection;
    int xangle;
    int yangle;

  public:
    Camera(float fov, float ar, float near, float far);
    Camera(float left, float right, float top, float bottom, float near, float far);
    ~Camera();
    const Maths::Matrix4 &Projection();
    void turn(int x, int y);
    void lookAt(const Maths::Vector3 &v);

  private:
    void recalculate() override;
};