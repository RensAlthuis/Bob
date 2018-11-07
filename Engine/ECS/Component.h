#pragma once
#include <vector>
#include <stdLib.h>

namespace Engine
{
namespace ECS
{
class IComponent
{
  private:
    static std::vector<size_t> typeInfo;
    int id;

  public:
    static int registerComponentType(size_t size);

    inline static size_t TypeSize(int type)
    {
        return typeInfo[type];
    }

    inline int ID(){return id;}
};

template <typename T>
class Component : public IComponent
{
  public:
    static const int TYPE;
    static const int SIZE;


  private:
};

template <typename T>
const int Component<T>::TYPE(IComponent::registerComponentType(sizeof(T)));

template <typename T>
const int Component<T>::SIZE(sizeof(T));

}; // namespace ECS
}; // namespace Engine