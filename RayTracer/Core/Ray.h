#pragma once
#include "Vector.h"

class Ray
{
public:

    Ray(const Vec4D& origin, const Vec4D& direction);

    const Vec4D& GetOrigin() const { return m_origin; }
    const Vec4D& GetDirection() const { return m_direction; }

    Vec4D GetPointAtDistance(float distance) const;

private:

    Vec4D m_origin;
    Vec4D m_direction;
    Vec4D m_normalizedDirection;
};