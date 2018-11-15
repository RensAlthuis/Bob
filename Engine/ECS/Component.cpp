#include "Component.h"

namespace Engine
{
namespace ECS
{

// as stated in the header file, on windows the following is just fine..
// std::vector<TypeData> IComponent::typeInfo;
// on some linux machines however..
std::vector<TypeData> &IComponent::typeInfo()
{
    static std::vector<TypeData> typeinfo;
    return typeinfo;
}

int IComponent::registerComponentType(size_t size, createFunc cf, freeFunc ff)
{
    int index = IComponent::typeInfo().size();
    IComponent::typeInfo().push_back(TypeData(size, cf, ff));
    return index;
}
}; // namespace ECS
}; // namespace Engine