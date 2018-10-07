#pragma once
#include "Maths/Maths.h"

namespace Engine{
class Object
{
  protected:
    Maths::Vector3 translation;
    Maths::Quaternion rotation;
    float scale;
    Maths::Matrix4 transform;

  public:
    Object();
    ~Object();

    const Maths::Vector3 Front() const;
    const Maths::Matrix4& Transform() const;
    void translate(Maths::Vector3 v, bool inWorldSpace);
    void translate(float x, float y, float z, bool inWorldSpace);
    void rotate(Maths::Quaternion q);

  protected:
    virtual void recalculate();
};

};