#pragma once
#include "Maths/Maths.h"

namespace Engine
{

class Transform
{

   private:
     Maths::Vector3 scaling;
     Maths::Matrix4 transform;
     Maths::Matrix4 modelMatrix;
     Maths::Quaternion rotation;
     Maths::Vector3 translation;
     bool dirty;

     void recalculate();

   public:
     Transform();
     inline const Maths::Matrix4 &Matrix()
     {
          if (dirty)
               recalculate();
          return transform;
     }

     inline const Maths::Vector3 Front() const
     {
          return Maths::Vector3(transform[2], transform[6], transform[10]);
     }

     void translate(Maths::Vector3 v, bool inWorldSpace);
     inline void translate(float x, float y, float z, bool inWorldSpace)
     {
          translate(Maths::Vector3(x, y, z), inWorldSpace);
     }

     void rotate(Maths::Quaternion q);
     void lookAt(const Maths::Vector3 &v);
     void scale(Maths::Vector3 s, bool set = false);
};

}; // namespace Engine