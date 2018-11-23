#pragma once

#include "../ECS/Component.h"
#include "../Model.h"

namespace Engine
{
struct ModelComponent : public ECS::Component<ModelComponent>
{
    Model *model;
};
} // namespace Engine
