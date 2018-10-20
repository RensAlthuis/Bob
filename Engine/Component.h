#pragma once

namespace Engine
{

class Component
{
  public:
    virtual void update(){};
    virtual void start(){};
    Component(){};
    virtual ~Component(){};
};
}; // namespace Engine