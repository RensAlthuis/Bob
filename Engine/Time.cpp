#include "Time.h"

namespace Engine{

long Time::oldTime = time();
float Time::deltaTime = 0;

long Time::time(){

    return (std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
            ).count());
}

float Time::deltatime(){
    return deltaTime;
}

};
