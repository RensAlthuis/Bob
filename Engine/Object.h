#pragma once
#include "Maths/Maths.h"

namespace Engine{
class Object
{
  protected:
    Maths::Quaternion rotation;
    float scale;
    Maths::Matrix4 transform;

  public:
    Object();
    ~Object();

    Maths::Vector3 translation;
    const Maths::Vector3 Front() const;
    const Maths::Matrix4& Transform() const;
    void translate(Maths::Vector3 v, bool inWorldSpace);
    void translate(float x, float y, float z, bool inWorldSpace);
    void rotate(Maths::Quaternion q);
    void lookAt(const Maths::Vector3 &v);
    void scaleAll(float s); 

  protected:
    virtual void recalculate();
};

};