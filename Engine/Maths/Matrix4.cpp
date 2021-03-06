#include "Matrix4.h"

namespace Engine{
namespace Maths
{

Matrix4::Matrix4()
{
    memset(&mat, 0, sizeof(float) * 16);
}

Matrix4::~Matrix4()
{
}

Matrix4 Matrix4::identity()
{
    Matrix4 m;
    m.mat[0] = 1;
    m.mat[5] = 1;
    m.mat[10] = 1;
    m.mat[15] = 1;
    return m;
}
Matrix4 Matrix4::scale(float x, float y, float z)
{
    Matrix4 m = identity();
    m.mat[0] = x;
    m.mat[5] = y;
    m.mat[10] = z;
    m.mat[15] = 1;
    return m;
}

Matrix4 Matrix4::translate(const Vector3 &v)
{
    return translate(v.x, v.y, v.z);
}

Matrix4 Matrix4::translate(float x, float y, float z)
{
    Matrix4 m = identity();
    m.mat[12] = x;
    m.mat[13] = y;
    m.mat[14] = z;
    m.mat[15] = 1;
    return m;
}

Matrix4 Matrix4::rotate(const Quaternion &q)
{
    float s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

    s = 2.0f;
    xs = s * q.x;
    wx = q.w * xs;
    xx = q.x * xs;

    ys = s * q.y;
    wy = q.w * ys;
    xy = q.x * ys;
    yy = q.y * ys;

    zs = s * q.z;
    wz = q.w * zs;
    xz = q.x * zs;
    yz = q.y * zs;
    zz = q.z * zs;

    Matrix4 m;
    m.mat[0] = 1.0f - (yy + zz);
    m.mat[1] = xy + wz;
    m.mat[2] = xz - wy;

    m.mat[4] = xy - wz;
    m.mat[5] = 1.0f - (xx + zz);
    m.mat[6] = yz + wx;

    m.mat[8] = xz + wy;
    m.mat[9] = yz - wx;
    m.mat[10] = 1.0f - (xx + yy);

    m.mat[15] = 1;
    return m;
}

Matrix4 Matrix4::rotateAxisAngle(float angle, float x, float y, float z)
{
    Matrix4 m;

    float rads = angle * ((float)M_PI / 180.0f);
    float c = cos(rads);
    float s = sin(rads);
    float oneminc = 1 - c;

    m.mat[0] = c + x * x * oneminc;
    m.mat[1] = y * x * oneminc + z * s;
    m.mat[2] = z * x * oneminc - y * s;
    m.mat[4] = x * y * oneminc - z * s;
    m.mat[5] = c + y * y * oneminc;
    m.mat[6] = z * y * oneminc + x * s;
    m.mat[8] = x * z * oneminc + y * s;
    m.mat[9] = y * z * oneminc - x * s;
    m.mat[10] = c + z * z * oneminc;
    m.mat[15] = 1;
    return m;
}

Matrix4 Matrix4::ortho(float left, float right, float bottom, float top, float near, float far)
{
    Matrix4 m;
    m.mat[0] = 2 / (right - left);
    m.mat[5] = 2 / (top - bottom);
    m.mat[10] = -2 / (far - near);
    m.mat[12] = -((right + left) / (right - left));
    m.mat[13] = -((top + bottom) / (top - bottom));
    m.mat[14] = -((far + near) / (far - near));
    m.mat[15] = 1;
    return m;
}

Matrix4 Matrix4::perspective(float fov, float aspect, float near, float far)
{
    float tfo2 = tan(((float)M_PI / 180.0f) * fov / 2.0f);

    Matrix4 m;
    m.mat[0] = 1 / (aspect * tfo2);
    m.mat[5] = 1 / tfo2;
    m.mat[10] = (far + near) / (near - far);
    m.mat[11] = -1;
    m.mat[14] = (2 * far * near) / (near - far);
    return m;
}

Matrix4 Matrix4::obliquePerspective(float left, float right, float bottom, float top, float near, float far)
{

    float rml = right - left;
    float rpl = right + left;
    float tmb = top - bottom;
    float tpb = top + bottom;
    float n2 = 2*near;
    float nmf = near - far;
    float npf = near + far;
    Matrix4 m;
    m.mat[0] = n2 / rml;
    m.mat[5] = n2 / tmb;
    m.mat[8] = rpl/rml;
    m.mat[9] = tpb/tmb;
    m.mat[10] = npf/nmf;
    m.mat[11] = -1;
    m.mat[14] = (n2*far)/nmf;
    return m;
}

float Matrix4::operator[](unsigned int index) const
{
    return mat[index];
}

void Matrix4::setRows(const Vector3 &a, const Vector3 &b, const Vector3 &c)
{
        mat[0] = a.x;
        mat[1] = b.x;
        mat[2] = c.x;
        mat[3] = 0;
        mat[4] = a.y;
        mat[5] = b.y;
        mat[6] = c.y;
        mat[7] = 0;
        mat[8] = a.z;
        mat[9] = b.z;
        mat[10] = c.z;
        mat[11] = 0;
        mat[12] = 0;
        mat[13] = 0;
        mat[14] = 0;
        mat[15] = 1;
}

void Matrix4::setCol(int i, const Vector4 &v)
{
    if(i > 3) return;
    mat[i*4 + 0] = v.x;
    mat[i*4 + 1] = v.y;
    mat[i*4 + 2] = v.z;
    mat[i*4 + 3] = v.w;
}

Matrix4 operator+(const Matrix4 &l, float r)
{
    Matrix4 m;
    for (int i = 0; i < 16; i++)
    {
        m.mat[i] = l.mat[i] + r;
    }
    return m;
}

Matrix4 operator-(const Matrix4 &l, float r)
{
    Matrix4 m;
    for (int i = 0; i < 16; i++)
    {
        m.mat[i] = l.mat[i] + r;
    }
    return m;
}
Matrix4 operator*(const Matrix4 &l, float r)
{
    Matrix4 m;
    for (int i = 0; i < 16; i++)
    {
        m.mat[i] = l.mat[i] + r;
    }
    return m;
}

Matrix4 operator+(const Matrix4 &l, const Matrix4 &r)
{
    Matrix4 m;
    for (int i = 0; i < 16; i++)
    {
        m.mat[i] = l.mat[i] + r.mat[i];
    }
    return m;
}

Matrix4 operator-(const Matrix4 &l, const Matrix4 &r)
{
    Matrix4 m;
    for (int i = 0; i < 16; i++)
    {
        m.mat[i] = l.mat[i] + r.mat[i];
    }
    return m;
}

Matrix4 operator*(const Matrix4 &l, const Matrix4 &r)
{
    Matrix4 m;
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            float sum = 0;
            for (int i = 0; i < 4; i++)
            {
                sum += l[i * 4 + y] * r[x * 4 + i];
            }
            m.mat[x * 4 + y] = sum;
        }
    }
    return m;
}

std::ostream &operator<<(std::ostream &out, const Matrix4 &mat)
{
    out << "(" << std::endl;

    for (int j = 0; j < 4; j++)
    {
        {
            for (int i = 0; i < 4; i++)
                out << mat.mat[i * 4 + j] << ", ";
        }
        out << std::endl;
    }
    out << ")";
    return out;
}

Vector3 operator*(const Matrix4 &r, const Vector3 &l)
{
    return Vector3(
        r[0] * l.x + r[4] * l.y + r[8] * l.z + r[12],
        r[1] * l.x + r[5] * l.y + r[9] * l.z + r[13],
        r[2] * l.x + r[6] * l.y + r[10] * l.z + r[14]);
}

}; // namespace Maths
};