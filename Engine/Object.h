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
  inline const Maths::Matrix4 &Transform() const { return transform; }
  inline const Maths::Vector3 Front() const { return Maths::Vector3(transform[2], transform[6], transform[10]); }
  void translate(Maths::Vector3 v, bool inWorldSpace);
  void translate(float x, float y, float z, bool inWorldSpace);
  void rotate(Maths::Quaternion q);
  void lookAt(const Maths::Vector3 &v);
  void scale(Maths::Vector3 s);
  void update();
  void addComponent(Component &component);
  void addChild(Object &object);
public:
  virtual void recalculate();
};

}; // namespace Engine