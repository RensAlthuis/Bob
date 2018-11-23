#pragma once
#include "../ECS/Component.h"
#include "../Material.h"
#include "../Shader.h"

namespace Engine
{

struct RenderComponent : public ECS::Component<RenderComponent>
{
    Material *mat;
    Shader *shader;
};

} // namespace Engine