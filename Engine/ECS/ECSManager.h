#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <cstring>
#include "Component.h"
#include "SystemGroup.h"

namespace Engine
{
namespace ECS
{

typedef std::pair<int, std::vector<std::pair<int, int>>> Entity;
class ECSManager
{
  private:
    std::map<int, std::vector<char>> components; // type -> componentOfType
    std::vector<Entity*> entities;
    std::vector<int> system;

  public:
    ~ECSManager();
    template <typename T>
    inline T *getComponent(Entity* entity)
    {
        return (T *)getComponent(entity, T::TYPE);
    }

    template <typename T>
    inline void removeComponent(Entity* entity)
    {
        removeComponent(entity, T::TYPE);
    }

    template <typename... T>
    Entity* createEntity(T*... comps)
    {
        int types[] = {(T::TYPE)...};
        IComponent* c[] = {((IComponent*)comps)...};
        return createEntity(types, sizeof...(T), c);
    };

    void updateSystems(float deltaTime, SystemGroup& systems);
  private:
    
    IComponent *getComponent(Entity* entity, int type);
    void addComponent(Entity* entity, int type, IComponent* comp);
    void deleteComponent(int type, int index);
    void removeComponent(Entity* entity, int type);

    Entity* createEntity(int* ComponentTypes, int numComponentsm, IComponent** comps);
    void removeEntity(Entity* entity);

};

}; // namespace ECS
}; // namespace Engine