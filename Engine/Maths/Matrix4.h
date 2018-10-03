#pragma once
#include <iostream>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Maths.h"

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
	static Matrix4 translate(const Vector3& v);
	static Matrix4 rotate(const Quaternion& q);
	static Matrix4 rotateAxisAngle(float angle, float x, float y, float z);
	static Matrix4 ortho(float left, float right, float top, float bottom, float near, float far);
	static Matrix4 perspective(float fov, float aspect, float near, float far);
	static Matrix4 obliquePerspective(float left, float right, float bottom, float top, float near, float far);

  public:
	float operator[](unsigned int index) const;
	void setRows(const Vector3 &a, const Vector3 &b, const Vector3 &c);
	void setCol(int i, const Vector4 &v);
	friend Matrix4 operator+(const Matrix4 &l, float r);
	friend Matrix4 operator-(const Matrix4 &l, float r);
	friend Matrix4 operator*(const Matrix4 &l, float r);
	friend Matrix4 operator+(const Matrix4 &l, const Matrix4 &r);
	friend Matrix4 operator-(const Matrix4 &l, const Matrix4 &r);
	friend Matrix4 operator*(const Matrix4 &l, const Matrix4 &r);
	friend Vector3 operator*(const Matrix4 &r, const Vector3 &l);
	friend std::ostream &operator<<(std::ostream &out, const Matrix4 &r);
};

} // namespace Maths
