#pragma once
#include "Matrix.h"

class Transform
{
public:

    static Matrix<4, 4> Translation(float x, float y = 0.f, float z = 0.f) { return Translation({ x, y, z }); }
    static Matrix<4, 4> Translation(const Vec3D& vec);

    static Matrix<4, 4> Scaling(float x, float y = 0.f, float z = 0.f) { return Scaling({ x, y, z }); }
    static Matrix<4, 4> Scaling(const Vec3D& vec);

    static Matrix<4, 4> RotationX(float rad);
    static Matrix<4, 4> RotationY(float rad);
    static Matrix<4, 4> RotationZ(float rad);

    static Matrix<4, 4> Shearing(float xy, float xz, float yx, float yz, float zx, float zy);

private:


};