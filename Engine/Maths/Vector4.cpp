#include "Vector4.h"

namespace Engine{
namespace Maths
{

const Vector4 Vector4::Zero(0,0,0,0);

Vector4::Vector4()
 : x(0), y(0), z(0), w(0)
{}

Vector4::Vector4(float x, float y, float z, float w)
 : x(x), y(y), z(z), w(w)
{}

Vector4 operator+(const Vector4 &l, float r)
{
    return Vector4(
        l.x + r,
        l.y + r,
        l.z + r,
        l.w + r);
}

Vector4 operator-(const Vector4 &l, float r)
{
    return Vector4(
        l.x - r,
        l.y - r,
        l.z - r,
        l.w - r);
}

Vector4 operator*(const Vector4 &l, float r)
{
    return Vector4(
        l.x * r,
        l.y * r,
        l.z * r,
        l.w * r);
}

Vector4 operator/(const Vector4 &l, float r)
{
    return Vector4(
        l.x / r,
        l.y / r,
        l.z / r,
        l.w / r);
}

Vector4 operator-(const Vector4 &l)
{
    return Vector4(
        -l.x,
        -l.y,
        -l.z,
        -l.w);
}

Vector4 operator+(const Vector4 &l, const Vector4 &r)
{
    return Vector4(
        l.x + r.x,
        l.y + r.y,
        l.z + r.z,
        l.w + r.w);
}

Vector4 operator-(const Vector4 &l, const Vector4 &r)
{
    return Vector4(
        l.x - r.x,
        l.y - r.y,
        l.z - r.z,
        l.w - r.w);
}

Vector4 operator*(const Vector4 &l, const Matrix4 &r)
{
    return Vector4(
        r[0] * l.x + r[4] * l.y + r[8] * l.z + r[12] * l.w,
        r[1] * l.x + r[5] * l.y + r[9] * l.z + r[13] * l.w,
        r[2] * l.x + r[6] * l.y + r[10] * l.z + r[14] * l.w,
        r[3] * l.x + r[7] * l.y + r[11] * l.z + r[15] * l.w);
}

std::ostream &operator<<(std::ostream &out, const Vector4 &r)
{
    return out << "(" << r.x << ", " << r.y << ", " << r.z << ", " << r.w << ")";
}

float Vector4::dot(const Vector4 &other)
{
    return (x * other.x + y * other.y + z * other.z + w * other.w);
}

// length
float Vector4::length()
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

Vector4::~Vector4()
{
}

}; // namespace Maths
};