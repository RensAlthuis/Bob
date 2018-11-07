#pragma once
#include <vector>
#include <map>

namespace Engine
{
namespace ECS
{
class ECS
{
  private:
    std::map<int, std::vector<char>> components; // id -> components
    //list of entities
    //list of systems

    // void* getEntity(int entityID);
    // int createEntity();
    // void destroyEntity();

    // // template <typename T>
    // // T* getComponent<T>(int entityID);

    // int createEntity();
    // void destroyEntity();

    //getComponent
    //update systems?


  public:
};
}; // namespace ECS
}; // namespace Engine