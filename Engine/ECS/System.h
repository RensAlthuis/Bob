#pragma once
#include "Component.h"

namespace Engine
{
namespace ECS
{
class System
{
    private:
        int priority;
        bool enabled;
    public:
        void update(float deltaTime);
};
}; // namespace ECS
}; // namespace Engine
