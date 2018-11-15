#include "System.h"

namespace Engine
{
namespace ECS
{

System::System()
{
}
void System::addComponentTypes(int* componentTypes, int nTypes)
{
    for(int i = 0; i < nTypes; i++)
    {
        types.push_back(componentTypes[i]);
    }
};

void System::addComponentType(int type)
{
    types.push_back(type);
}

};
}; // namespace Engine