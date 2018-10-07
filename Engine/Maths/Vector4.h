#pragma once
#include <math.h>
#include <iostream>
#include "Matrix4.h"

namespace Engine{
namespace Maths
{

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

public:
	Vector4(float x, float y, float z, float w);
	~Vector4();

	friend Vector4 operator+(const Vector4 &l, float r);
	friend Vector4 operator-(const Vector4 &l, float r);
	friend Vector4 operator*(const Vector4 &l, float r);
	friend Vector4 operator/(const Vector4 &l, float r);
	friend Vector4 operator-(const Vector4 &l);
	friend Vector4 operator+(const Vector4 &l, const Vector4 &r);
	friend Vector4 operator-(const Vector4 &l, const Vector4 &r);
	friend Vector4 operator*(const Vector4 &l, const Matrix4 &r);
	friend std::ostream &operator<<(std::ostream &out, const Vector4 &v);
	float dot(const Vector4 &other);
	Vector4 cross(const Vector4 &other);
	float length();
};
}; // namespace Maths
};