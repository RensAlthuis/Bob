#include "Vector3.h"


namespace Engine{
namespace Maths
{

const Vector3 Vector3::Up(0, 1, 0);
const Vector3 Vector3::Forward(0, 0, -1);
const Vector3 Vector3::Right(1, 0, 0);
const Vector3 Vector3::Zero(0, 0, 0);

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

std::ostream &operator<<(std::ostream &out, const Vector3 &r)
{
    return out << "(" << r.x << ", " << r.y << ", " << r.z << ")";
}

float Vector3::dot(const Vector3 &other) const
{
    return (x * other.x + y * other.y + z * other.z);
}
// cross product
Vector3 Vector3::cross(const Vector3 &other) const
{
    Vector3 n = Vector3(
        (y * other.z) - (other.y * z),
        (x * other.z) - (other.x * z),
        (x * other.y) - (other.x * y));
    return n;
}

// length
float Vector3::length() const
{
    return sqrtf(x * x + y * y + z * z);
}

Vector3 Vector3::rotate(const Quaternion &q) const
{
    float vMult = 2.0f * (q.x * x + q.y * y + q.z * z);
    float crossMult = 2.0f * q.w;
    float pMult = crossMult * q.w - 1.0f;
    return Vector3(
        pMult * x + vMult * q.x + crossMult * (q.y * z - q.z * y),
        pMult * y + vMult * q.y + crossMult * (q.z * x - q.x * z),
        pMult * z + vMult * q.z + crossMult * (q.x * y - q.y * x));
}

Vector3 &Vector3::normalize()
{
    float magnitude = length();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
    return *this;
}

Vector3::~Vector3()
{
}

}; // namespace Maths
};