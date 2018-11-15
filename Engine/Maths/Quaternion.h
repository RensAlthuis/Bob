#pragma once
#include "Maths.h"

namespace Engine{
namespace Maths
{
class Quaternion
{
  public:
    float w, x, y, z;

  public:
    Quaternion():Quaternion(1,0,0,0){};
    Quaternion(float w, float x, float y, float z);
    Quaternion(float w, Vector3 v);
    static Quaternion fromAxisAngle(float angle, const Vector3 &axis);
    static Quaternion fromAxisAngle(float angle, float x, float y, float z);
    ~Quaternion();
    float dot(const Quaternion &q) const;
    Quaternion inverse() const;
    float length() const;
    Quaternion& normalize();

    friend Quaternion operator*(const Quaternion &l, const Quaternion &r);
    friend std::ostream &operator<<(std::ostream &out, const Quaternion &v);
};
}; // namespace Maths
};