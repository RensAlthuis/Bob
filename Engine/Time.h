#pragma once
#include <chrono>
#include <iostream>

namespace Engine
{
class Time
{

  private:
    static double deltaTime;
    static double oldTime;

  public:
    static double time();
    static double deltatime();

  private:
    friend class Window;
};
} // namespace Engine