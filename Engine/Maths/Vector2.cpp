#include "Vector2.h"

namespace Engine{
namespace Maths
{

Vector2::Vector2(float x, float y) : x(x),
                                     y(y)
{
}

Vector2 operator+(const Vector2 &l, float r)
{
    return Vector2(
        l.x + r,
        l.y + r);
}

Vector2 operator-(const Vector2 &l, float r)
{
    return Vector2(
        l.x - r,
        l.y - r);
}

Vector2 operator*(const Vector2 &l, float r)
{
    return Vector2(
        l.x * r,
        l.y * r);
}

Vector2 operator/(const Vector2 &l, float r)
{
    return Vector2(
        l.x / r,
        l.y / r);
}

Vector2 operator-(const Vector2 &l)
{
    return Vector2(
        -l.x,
        -l.y);
}

Vector2 operator+(const Vector2 &l, const Vector2 &r)
{
    return Vector2(
        l.x + r.x,
        l.y + r.y);
}

Vector2 operator-(const Vector2 &l, const Vector2 &r)
{
    return Vector2(
        l.x - r.x,
        l.y - r.y);
}

std::ostream &operator<<(std::ostream &out, const Vector2 &r)
{
    return out << "(" << r.x << ", " << r.y << ")";
}

float Vector2::dot(const Vector2 &other)
{
    return (x * other.x + y * other.y);
}

// length
float Vector2::length()
{
    return sqrtf(x * x + y * y);
}

Vector2::~Vector2()
{
}

}; // namespace Maths
};