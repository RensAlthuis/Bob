#include "SystemGroup.h"

namespace Engine
{
namespace ECS
{

SystemGroup::SystemGroup() : systems(){

}

void SystemGroup::addSystem(System* sys){
    systems.push_back(sys);
}

};
}; // namespace Engine