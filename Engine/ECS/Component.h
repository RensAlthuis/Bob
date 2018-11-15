#pragma once

#include <vector>
#include <tuple>
#include <iostream>

namespace Engine
{
namespace ECS
{

class IComponent;

typedef int (*createFunc)(std::vector<char> &memory, int entityID, IComponent* comp);
typedef void (*freeFunc)(IComponent *comp);
typedef std::tuple<size_t, createFunc, freeFunc> TypeData;

class IComponent
{
  private:
    // wrapping typeInfo in a static function fixes a weird bug on linux machines
    // real magic going on here...
    // on windows just writing it as
    // static std::vector<TypeData> typeInfo;
    // works just fine, but on some linux machines it gives segfaults the moment it's being used
    // in the main function. Suspecting something with dynamic initializion resetting the value
    // or multiple cpp compilation units having different global values for it??
    static std::vector<TypeData> &typeInfo();
  public:
    int entityID;
    // static int registerComponentType(size_t size, createFunc cf, freeFunc ff);
    // static int test();
    static int registerComponentType(size_t size, createFunc cf, freeFunc ff);
    inline static size_t TypeSize(int type) { return std::get<0>(typeInfo()[type]); }
    inline static createFunc CreateFunc(int type) { return std::get<1>(typeInfo()[type]); }
    inline static freeFunc FreeFunc(int type) { return std::get<2>(typeInfo()[type]); }
};


template <typename T>
class Component : public IComponent
{
  public:
    static const int TYPE;
    static const int SIZE;
    static const createFunc CREATEFUNC;
    static const freeFunc FREEFUNC;

  private:
};

template <typename T>
void componentFree(IComponent *comp)
{
    T *component = (T *)comp;
    component->~T();
};

// template <typename T>
// int componentCreate(std::vector<char> &memory, int entityID)
// {
//     int index = memory.size();
//     memory.resize(index + T::SIZE);
//     T *component = new (&memory[index]) T;
//     component->entityID = entityID;
//     return index;
// };

template <typename T>
int componentCreate(std::vector<char> &memory, int entityID, IComponent* comp)
{
    int index = memory.size();
    memory.resize(index + T::SIZE);
    T *component = new (&memory[index]) T(*(T*)comp);
    component->entityID = entityID;
    return index;
};

template <typename T>
const int Component<T>::TYPE(IComponent::registerComponentType(sizeof(T), componentCreate<T>, componentFree<T>));

template <typename T>
const createFunc Component<T>::CREATEFUNC(componentCreate<T>);

template <typename T>
const freeFunc Component<T>::FREEFUNC(componentFree<T>);

template <typename T>
const int Component<T>::SIZE(sizeof(T));

}; // namespace ECS
}; // namespace Engine