#pragma once
#include "ECS/System.h"
#include "Components/RenderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/ModelComponent.h"

namespace Engine
{

class RenderSystem : public ECS::System
{
  public:
    RenderSystem();

    void update(float deltaTime, ECS::IComponent **components) const override;

    void setMaterial(RenderComponent *render) const;
};
}; // namespace Engine