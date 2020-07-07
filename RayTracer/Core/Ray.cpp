#include "Core/Ray.h"

Ray::Ray(const Vec4D& origin, const Vec4D& direction)
    : m_origin(origin)
    , m_direction(direction)
    , m_normalizedDirection(direction.Normalize())
{

}

Vec4D Ray::GetPointAtDistance(float distance) const
{
    return m_origin + (m_normalizedDirection * distance);
}

