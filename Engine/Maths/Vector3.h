#pragma once
#include <math.h>
#include <iostream>
namespace Maths
{

class Vector3
{
public:
	float x;
	float y;
	float z;
	static const Vector3 Up;

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
	friend std::ostream &operator<<(std::ostream &out, const Vector3 &v);
	float dot(const Vector3 &other);
	Vector3 cross(const Vector3 &other);
	float length();
};
} // namespace Maths