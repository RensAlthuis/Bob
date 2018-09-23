#pragma once
#include <iostream>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Maths
{
class Matrix4
{
  public:
	Matrix4();
	~Matrix4();
	float mat[16];
	static Matrix4 identity();
	static Matrix4 scale(float x, float y, float z);
	static Matrix4 translate(float x, float y, float z);
	static Matrix4 rotate(float angle, float x, float y, float z);
	static Matrix4 ortho(float left,float right,float top,float bottom,float near, float far);
	static Matrix4 perspective(float fov, float aspect, float near, float far);

public:
	float operator[](unsigned int index) const;
	friend Matrix4 operator+(const Matrix4& l, float r);
	friend Matrix4 operator-(const Matrix4& l, float r);
	friend Matrix4 operator*(const Matrix4& l, float r);
	friend Matrix4 operator+(const Matrix4& l, const Matrix4& r);
	friend Matrix4 operator-(const Matrix4& l, const Matrix4& r);
	friend Matrix4 operator*(const Matrix4& l, const Matrix4& r);
	friend std::ostream& operator<<(std::ostream& out, const Matrix4& r);
};

} // namespace Maths
