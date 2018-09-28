#include "Vector3.h"

namespace Maths
{

Vector3::Vector3(float x, float y, float z) : x(x),
                                              y(y),
                                              z(z)
{
}

Vector3 operator+(const Vector3 &l, float r)
{
    return Vector3(
        l.x + r,
        l.y + r,
        l.z + r);
}

Vector3 operator-(const Vector3 &l, float r)
{
    return Vector3(
        l.x - r,
        l.y - r,
        l.z - r);
}

Vector3 operator*(const Vector3 &l, float r)
{
    return Vector3(
        l.x * r,
        l.y * r,
        l.z * r);
}

Vector3 operator/(const Vector3 &l, float r)
{
    return Vector3(
        l.x / r,
        l.y / r,
        l.z / r);
}

Vector3 operator-(const Vector3 &l)
{
    return Vector3(
        -l.x,
        -l.y,
        -l.z);
}

Vector3 operator+(const Vector3 &l, const Vector3 &r)
{
    return Vector3(
        l.x + r.x,
        l.y + r.y,
        l.z + r.z);
}

Vector3 operator-(const Vector3 &l, const Vector3 &r)
{
    return Vector3(
        l.x - r.x,
        l.y - r.y,
        l.z - r.z);
}

Vector3 operator*(const Vector3 &l, const Matrix4 &r)
{
    return Vector3(
        r[0] * l.x + r[4] * l.y + r[8] * l.z + r[12],
        r[1] * l.x + r[5] * l.y + r[9] * l.z + r[13],
        r[2] * l.x + r[6] * l.y + r[10] * l.z + r[14]);
}

std::ostream &operator<<(std::ostream &out, const Vector3 &r)
{
    return out << "(" << r.x << ", " << r.y << ", " << r.z << ")";
}

float Vector3::dot(const Vector3 &other)
{
    return (x * other.x + y * other.y + z * other.z);
}
// cross product
Vector3 Vector3::cross(const Vector3 &other)
{
    Vector3 n = Vector3(
        (y * other.z) - (other.y * z),
        (x * other.z) - (other.x * z),
        (x * other.y) - (other.x * y));
    return n;
}

// length
float Vector3::length()
{
    return sqrtf(x * x + y * y + z * z);
}

Vector3::~Vector3()
{
}

} // namespace Maths