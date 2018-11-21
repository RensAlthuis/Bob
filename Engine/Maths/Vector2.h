#pragma once
#include <math.h>
#include <iostream>
#include "Matrix4.h"

namespace Engine
{
namespace Maths
{

class Vector2
{
  public:
	float x;
	float y;

  public:
	Vector2(float x, float y);
	~Vector2();

	friend Vector2 operator+(const Vector2 &l, float r);
	friend Vector2 operator-(const Vector2 &l, float r);
	friend Vector2 operator*(const Vector2 &l, float r);
	friend Vector2 operator/(const Vector2 &l, float r);
	friend Vector2 operator-(const Vector2 &l);
	friend Vector2 operator+(const Vector2 &l, const Vector2 &r);
	friend Vector2 operator-(const Vector2 &l, const Vector2 &r);
	friend std::ostream &operator<<(std::ostream &out, const Vector2 &v);
	float dot(const Vector2 &other);
	Vector2 cross(const Vector2 &other);
	float length();
};
}; // namespace Maths
}; // namespace Engine