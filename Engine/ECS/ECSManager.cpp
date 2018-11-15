#include "ECSManager.h"

namespace Engine
{
namespace ECS
{

Entity *ECSManager::createEntity(int *componentTypes, int numTypes, IComponent **comps)
{
    int index = entities.size();
    Entity *e = new Entity();
    e->first = index;

    for (int i = 0; i < numTypes; i++)
    {
        //TODO errorcheck
        addComponent(e, componentTypes[i], comps[i]);
    }
    entities.push_back(e);
    return e;
}

IComponent *ECSManager::getComponent(Entity *entity, int type)
{
    auto &componentList = entity->second;
    for (int i = 0; i < componentList.size(); i++)
    {
        if (componentList[i].first == type)
        {
            int index = componentList[i].second;
            IComponent *p = (IComponent *)&components[type][index];
            return p;
        }
    }
    return nullptr;
}

void ECSManager::addComponent(Entity *entity, int type, IComponent *comp)
{
    createFunc fn = IComponent::CreateFunc(type);
    int index = fn(components[type], entity->first, comp);
    std::cout << "add comp to: " << entity->first << ", " << type << ":" << index;
    IComponent *v2 = (IComponent *)&components[type];
    IComponent *v = (IComponent *)&components[type][index];
    std::cout << " @ " << v << " in " << v2 << std::endl;
    entity->second.push_back(std::make_pair(type, index));
}

void ECSManager::deleteComponent(int type, int index)
{
    auto &componentMemory = components[type];
    freeFunc fn = IComponent::FreeFunc(type);
    size_t typeSize = IComponent::TypeSize(type);
    int srcIndex = componentMemory.size() - typeSize;

    IComponent *target = (IComponent *)(componentMemory[index]);
    IComponent *source = (IComponent *)(componentMemory[srcIndex]);
    fn(target);

    //update the source components entity
    Entity *e = entities[source->entityID];
    for (int i = 0; i < e->second.size(); i++)
    {
        if (e->second[i].first == type)
        {
            e->second[i].second = index;
            break;
        }
    }

    memcpy(target, source, typeSize);
    componentMemory.resize(srcIndex);
}

void ECSManager::removeComponent(Entity *entity, int type)
{
    int component = -1;
    int index;
    for (index = 0; index < entity->second.size(); index++)
    {
        if (entity->second[index].first == type)
        {
            deleteComponent(type, entity->second[index].second);
            entity->second[index] = entity->second[entity->second.size() - 1];
            entity->second.pop_back();
            break;
        }
    }
}

void ECSManager::removeEntity(Entity *entity)
{
    for (int i = 0; i < entity->second.size(); i++)
    {
        deleteComponent(entity->second[i].first, entity->second[i].second);
    }
    int index = entity->first;
    delete entities[index];
    entities[index] = entities[entities.size() - 1];
    entities[index]->first = index;
    entities.pop_back();
}

void ECSManager::updateSystems(float deltaTime, SystemGroup &systems)
{
    for (const System *sys : systems.get())
    {
        auto &types = sys->getTypes();
        auto &componentMemory = components[types[0]];
        size_t size = IComponent::TypeSize(types[0]);
        IComponent *comps[types.size()];

        if (types.size() == 1)
        {
            for (int i = 0; i < componentMemory.size(); i += size)
            {
                comps[0] = (IComponent *)(&componentMemory[i]);
                sys->update(deltaTime, comps);
            }
            return;
        }

        for (int i = 0; i < componentMemory.size(); i += size)
        {
            comps[0] = (IComponent *)&componentMemory[i];
            Entity *e = entities[comps[0]->entityID];
            bool isValid = true;
            for (int j = 0; j < types.size(); j++)
            {
                if (types[j] == 0)
                    continue;
                comps[j] = getComponent(e, types[j]);
                if (comps[j] == nullptr)
                {
                    isValid = false;
                    break;
                }
            }

            if (isValid)
            {
                sys->update(deltaTime, comps);
            }
        }
    }
}

ECSManager::~ECSManager()
{
    for (auto comp : components)
    {
        size_t size = IComponent::TypeSize(comp.first);
        freeFunc fn = IComponent::FreeFunc(comp.first);
        for (int i = 0; i < comp.second.size(); i += size)
        {
            fn((IComponent *)(&comp.second[i]));
        }
    }

    for (auto e : entities)
    {
        delete e;
    }
}

}; // namespace ECS
}; // namespace Engine
