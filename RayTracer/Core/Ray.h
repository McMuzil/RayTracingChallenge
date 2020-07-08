#pragma once
#include "Vector.h"
#include "Matrix.h"

class Ray
{
public:

    Ray(const Vec3D& origin, const Vec3D& direction);

    const Vec3D& GetOrigin() const { return m_origin; }
    const Vec3D& GetDirection() const { return m_direction; }

    Vec3D GetPointAtDistance(float distance) const;

    Ray Transform(const Matrix<4, 4>& translation) const;

private:

    Vec3D m_origin;
    Vec3D m_direction;
    Vec3D m_normalizedDirection;
};