#pragma once
#include <chrono>
#include <iostream>

namespace Engine{
class Time{

    private:
        static float deltaTime;
        static long oldTime;
    public:
        static long time();
        static float deltatime();

    private:
        friend class Window;
};
}