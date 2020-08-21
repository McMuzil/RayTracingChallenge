#pragma once
#include "Matrix.h"

class Transform
{
public:

    static Matrix<4, 4> Translation(float x, float y, float z) { return Translation({ x, y, z }); }
    static Matrix<4, 4> Translation(const Vec3D& vec);

    static Matrix<4, 4> Scaling(float x, float y, float z) { return Scaling({ x, y, z }); }
    static Matrix<4, 4> Scaling(const Vec3D& vec);

    static Matrix<4, 4> RotationX(float rad);
    static Matrix<4, 4> RotationY(float rad);
    static Matrix<4, 4> RotationZ(float rad);

    static Matrix<4, 4> Shearing(float xy, float xz, float yx, float yz, float zx, float zy);

    static Matrix<4, 4> LookAt(const Vec3D& from, const Vec3D& to, const Vec3D& up = Vec3D(0, 1, 0));
};