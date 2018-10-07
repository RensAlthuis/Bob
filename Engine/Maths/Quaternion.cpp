#include "Quaternion.h"

namespace Engine{
namespace Maths
{
Quaternion::Quaternion(float w, float x, float y, float z) : w(w),
                                                             x(x),
                                                             y(y),
                                                             z(z)
{
}
Quaternion::Quaternion(float w, Vector3 v) : Quaternion(w, v.x, v.y, v.z)
{
}

Quaternion::~Quaternion()
{
}

Quaternion Quaternion::fromAxisAngle(float angle, const Vector3 &axis)
{
    float qAngle= 0.5f * angle * ((float)M_PI / 180.0f);
    float sinmult = sinf(qAngle);

    Quaternion q(
        cosf(qAngle),
        axis.x*sinmult,
        axis.y*sinmult,
        axis.z*sinmult
    );
    return q;
}

float Quaternion::length() const
{
    return sqrtf(w * w + x * x + y * y + z * z);
}

Quaternion& Quaternion::normalize()
{
    float l = length();
    w = w / l;
    x = x / l;
    y = y / l;
    z = z / l;
    return *this;
}
float Quaternion::dot(const Quaternion &q) const
{
    return w * q.w + x * q.x + y * q.y + z * q.z;
}

Quaternion Quaternion::inverse() const
{
    return Quaternion(w, -x, -y, -z);
}

Quaternion operator*(const Quaternion &l, const Quaternion &r)
{
    Vector3 vl(l.x, l.y, l.z);
    Vector3 vr(r.x, r.y, r.z);

    float w = l.w * r.w - vr.dot(vl);
    Vector3 v = vl * r.w + vr * l.w + vl.cross(vr);
    Quaternion q(w,v); 
    q.normalize();
    return q;
}

std::ostream &operator<<(std::ostream &out, const Quaternion &r)
{
    return out << "(" << r.w << ", " << r.x << ", " << r.y << ", " << r.z << ")";
}
}; // namespace Maths
};