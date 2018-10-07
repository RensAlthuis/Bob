#pragma once
#include <math.h>
#include <iostream>
#include "Maths.h"

namespace Engine{
namespace Maths
{

class Vector3
{
public:
	float x;
	float y;
	float z;
	static const Vector3 Up;
	static const Vector3 Forward;
	static const Vector3 Right;

public:
	Vector3():Vector3(0,0,0){};
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
	Vector3 &normalize();
	float dot(const Vector3 &other) const;
	Vector3 cross(const Vector3 &other) const;
	float length() const;
	Vector3 rotate(const Quaternion& q) const;
};
}; // namespace Maths
};