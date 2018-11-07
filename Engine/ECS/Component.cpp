#include "Component.h"

namespace Engine
{
namespace ECS
{
std::vector<size_t> IComponent::typeInfo;

int IComponent::registerComponentType(size_t size)
{
    int type = IComponent::typeInfo.size();
    IComponent::typeInfo.push_back(size);
    return type;
}
}; // namespace ECS
}; // namespace Engine