#pragma once
#include "Object.h"

namespace Engine
{

class Component
{
public:
  Object *parent;
  virtual void update(){};
  virtual void start(){};
  Component(){};
  virtual ~Component(){};
};
}; // namespace Engine