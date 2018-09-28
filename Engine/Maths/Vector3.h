#pragma once
#include <math.h>
#include <iostream>
#include "Matrix4.h"
namespace Maths
{

class Vector3
{
public:
	float x;
	float y;
	float z;

public:
	Vector3(float x, float y, float z);
	~Vector3();

	friend Vector3 operator+(const Vector3 &l, float r);
	friend Vector3 operator-(const Vector3 &l, float r);
	friend Vector3 operator*(const Vector3 &l, float r);
	friend Vector3 operator/(const Vector3 &l, float r);
	friend Vector3 operator-(const Vector3 &l);
	friend Vector3 operator+(const Vector3 &l, const Vector3 &r);
	friend Vector3 operator-(const Vector3 &l, const Vector3 &r);
	friend Vector3 operator*(const Vector3 &l, const Matrix4 &r);
	friend std::ostream &operator<<(std::ostream &out, const Vector3 &v);
	float dot(const Vector3 &other);
	Vector3 cross(const Vector3 &other);
	float length();
};
} // namespace Maths