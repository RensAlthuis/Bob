#include "Time.h"
#include <GLFW/glfw3.h>

namespace Engine
{

double Time::oldTime = time();
double Time::deltaTime = 0;

double Time::time()
{

    return glfwGetTime();
}

double Time::deltatime()
{
    return deltaTime;
}

}; // namespace Engine
