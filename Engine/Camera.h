#pragma once
#include "Maths/Maths.h"
#include <iostream>

class Camera
{

    private:
        Maths::Vector3 pos;
        int rotX;
        int rotY;
		Maths::Matrix4 transform;
        Maths::Matrix4 projection;

    public:
        Camera(float fov, float ar, float near, float far);
        Camera(float left, float right, float top, float bottom, float near, float far);
        ~Camera();
        const Maths::Matrix4& Transform();
        const Maths::Vector3 Front();
        const Maths::Matrix4& Projection();
        void move(float forward, float up, float right);
        void rotate(int x, int y);
    private:
        void recalculate();
};