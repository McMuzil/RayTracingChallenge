#pragma once
#include "Vector.h"

class Ray
{
public:

    Ray(const Vec3D& origin, const Vec3D& direction);

    const Vec3D& GetOrigin() const { return m_origin; }
    const Vec3D& GetDirection() const { return m_direction; }

    Vec3D GetPointAtDistance(float distance) const;

private:

    Vec3D m_origin;
    Vec3D m_direction;
    Vec3D m_normalizedDirection;
};