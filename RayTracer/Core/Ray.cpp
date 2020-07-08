#include "Core/Ray.h"

Ray::Ray(const Vec3D& origin, const Vec3D& direction)
    : m_origin(origin)
    , m_direction(direction)
    , m_normalizedDirection(direction.Normalize())
{

}

Vec3D Ray::GetPointAtDistance(float distance) const
{
    return m_origin + (m_normalizedDirection * distance);
}

Ray Ray::Transform(const Matrix<4, 4>& translation) const
{
    return Ray(Vec3D(translation * m_origin.AsPoint()), Vec3D(translation * m_direction.AsVector()));
}

