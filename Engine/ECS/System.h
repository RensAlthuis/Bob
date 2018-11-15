#pragma once
#include "Component.h"

namespace Engine
{
namespace ECS
{
class System
{
    protected:
        std::vector<int> types;
        System();
    public:
        virtual void update(float deltaTime, IComponent** components) const = 0;
        inline const std::vector<int>& getTypes() const{return types;};
        void addComponentTypes(int* addComponentTypes, int nTypes);
        void addComponentType(int type);
};
}; // namespace ECS
}; // namespace Engine
