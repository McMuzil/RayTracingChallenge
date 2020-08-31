#include "RayTracer/Core/Objects/Cube.h"

#include "RayTracer/Core/CollisionInfo.h"
#include "RayTracer/Core/Ray.h"

CollisionInfo Cube::IntersectInternal(const Ray& localRay) const
{
    Vec2D xMinMax = CheckAxis(localRay.GetOrigin().x, localRay.GetDirection().x);
    Vec2D yMinMax = CheckAxis(localRay.GetOrigin().y, localRay.GetDirection().y);
    Vec2D zMinMax = CheckAxis(localRay.GetOrigin().z, localRay.GetDirection().z);

    float minDistance = std::max({ xMinMax.x, yMinMax.x, zMinMax.x });
    float maxDistance = std::min({ xMinMax.y, yMinMax.y, zMinMax.y });

    if (minDistance > maxDistance)
    {
        return CollisionInfo();
    }

    CollisionInfo info;
    info.hits.emplace_back(minDistance, this);
    info.hits.emplace_back(maxDistance, this);

    return info;
}

Vec3D Cube::LocalNormalAt(const Vec3D& point) const
{
    const Vec3D absVec = point.Abs();
    const float maxValue = std::max({ absVec.x, absVec.y, absVec.z });

    if (maxValue == absVec.x)
    {
        return Vec3D(point.x, 0.f, 0.f);
    }
    else if (maxValue == absVec.y)
    {
        return Vec3D(0.f, point.y, 0.f);
    }
    else
    {
        return Vec3D(0.f, 0.f, point.z);
    }
}

Vec2D Cube::CheckAxis(float origin, float direction) const
{
    float minNumerator = (-1 - origin);
    float maxNumerator = (1 - origin);

    Vec2D minMax;

    if (abs(direction) <= Constants::Epsilon)
    {
        minMax.x = minNumerator * std::numeric_limits<float>::infinity();
        minMax.y = maxNumerator * std::numeric_limits<float>::infinity();
    }
    else
    {
        minMax.x = minNumerator / direction;
        minMax.y = maxNumerator / direction;
    }

    if (minMax.x > minMax.y)
    {
        std::swap(minMax.x, minMax.y);
    }

    return minMax;
}
