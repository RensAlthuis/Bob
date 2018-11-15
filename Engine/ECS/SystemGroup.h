#pragma once
#include <vector>
#include "System.h"
#include <iterator>

namespace Engine
{
namespace ECS
{

class SystemGroup
{
  private:
    std::vector<System*> systems;

  public:
    SystemGroup();
    void addSystem(System* system);
    inline const std::vector<System*> &get(){return systems;};
    // inline auto begin() noexcept { return systems.begin(); }
    // inline const auto cbegin() const noexcept { return systems.cbegin(); }
    // inline auto end() noexcept { return systems.end(); }
    // inline const auto cend() const noexcept { return systems.cend(); }

};

}; // namespace ECS

}; // namespace Engine