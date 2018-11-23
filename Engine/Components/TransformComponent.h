#pragma once
#include "../ECS/Component.h"
#include "../Transform.h"

namespace Engine
{
struct TransformComponent : public ECS::Component<TransformComponent>
{
    TransformComponent *Parent;
    Transform transform;
};
}; // namespace Engine