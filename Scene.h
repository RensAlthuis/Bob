#pragma once
#include <vector>
#include "Object.h"

namespace Engine
{

class Scene
{
  private:
    std::vector<Object *> children;

  private:
    void setLights();
  public:
    void addChild(Object *object);
    void update();
};
}; // namespace Engine