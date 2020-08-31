#include "Plane.h"

#include "RayTracer/Core/CollisionInfo.h"
#include "RayTracer/Core/Ray.h"

CollisionInfo Plane::IntersectInternal(const Ray& localRay) const
{
    if (abs(localRay.GetDirection().y) < Constants::Epsilon)
    {
        return CollisionInfo();
    }

    const Ray ray = localRay.Transform(GetTransform());

    CollisionInfo collisionInfo;

    const float distance = -localRay.GetOrigin().y / localRay.GetDirection().y;
    Hit& hit1 = collisionInfo.hits.emplace_back(distance, this);

    return collisionInfo;
}

Vec3D Plane::LocalNormalAt(const Vec3D& point) const
{
    return Vec3D(0, 1, 0);
}
