#include "Core/Transform.h"

Matrix<4, 4> Transform::Translation(const Vec3D& vec)
{
    Matrix<4, 4> translation = Matrix<4, 4>::Identity();
    translation.SetColumn(3, vec);

    return translation;
}

Matrix<4, 4> Transform::Scaling(const Vec3D& vec)
{
    Matrix<4, 4> scaling = Matrix<4, 4>::Identity();

    for (size_t i = 0; i < vec.Size; i++)
    {
        scaling[i][i] = vec[i];
    }

    return scaling;
}

Matrix<4, 4> Transform::RotationX(float rad)
{
    return Matrix<4, 4> (
        { 1.f,   0.f,       0.f,    0.f },
        { 0.f, cos(rad), -sin(rad), 0.f },
        { 0.f, sin(rad),  cos(rad), 0.f },
        { 0.f,   0.f,       0.f,    1.f }
    );
}

Matrix<4, 4> Transform::RotationY(float rad)
{
    return Matrix<4, 4>(
        {  cos(rad), 0.f, sin(rad), 0.f },
        {    0.f,    1.f,   0.f,    0.f },
        { -sin(rad), 0.f, cos(rad), 0.f },
        {    0.f,    0.f,   0.f,    1.f }
    );
}

Matrix<4, 4> Transform::RotationZ(float rad)
{
    return Matrix<4, 4>(
        { cos(rad), -sin(rad), 0.f, 0.f },
        { sin(rad),  cos(rad), 0.f, 0.f },
        {   0.f,       0.f,    1.f, 0.f },
        {   0.f,       0.f,    0.f, 1.f }
    );
}

Matrix<4, 4> Transform::Shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
    return Matrix<4, 4>(
        { 1,  xy, xz, 0 },
        { yx, 1,  yz, 0 },
        { zx, zy, 1,  0 },
        { 0,  0,  0,  1 }
    );
}
