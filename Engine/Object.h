#pragma once
#include "Maths/Maths.h"
#include <vector>
namespace Engine
{
class Component;
class Object
{
protected:
  Maths::Vector3 scaling;
  Maths::Matrix4 transform;
  std::vector<Component *> components;
  std::vector<Object *> children;
  Object *parent;

public:
  Maths::Quaternion rotation;
  Maths::Vector3 translation;
  Object();
  ~Object();
  const Maths::Vector3 Front() const;
  const Maths::Matrix4 &Transform() const;
  void translate(Maths::Vector3 v, bool inWorldSpace);
  void translate(float x, float y, float z, bool inWorldSpace);
  void rotate(Maths::Quaternion q);
  void lookAt(const Maths::Vector3 &v);
  void scale(Maths::Vector3 s);
  void update();
  void addComponent(Component *component);
  void addChild(Object *object);

public:
  virtual void recalculate();
};

}; // namespace Engine