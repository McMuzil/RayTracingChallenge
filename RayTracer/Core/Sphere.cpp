#include "Core/Sphere.h"

Vec3D Sphere::NormalAt(const Vec3D& point) const
{
    const Matrix<4, 4> inverseTrans = GetTransform().Inverse();
    const Vec3D pointObjSpace = inverseTrans * point.AsPoint();
    const Vec3D normalObjSpace = pointObjSpace - Vec3D(0.f); // We assume that the sphere is always at (0.0.0) position
    const Vec3D normalWorldSpace = inverseTrans.Transpose() * normalObjSpace.AsPoint();

    return normalWorldSpace.Normalize();
}
