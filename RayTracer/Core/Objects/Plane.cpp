#include "Plane.h"

#include "RayTracer/Core/CollisionInfo.h"
#include "RayTracer/Core/Ray.h"

CollisionInfo Plane::IntersectInternal(const Ray& ray) const
{
    const Ray localRay = ray.Transform(GetTransform().Inverse());

    if (abs(localRay.GetDirection().y) < Constants::Epsilon)
    {
        return CollisionInfo();
    }

    CollisionInfo collisionInfo;

    Hit& hit1 = collisionInfo.hits.emplace_back();
    hit1.distance = -localRay.GetOrigin().y / localRay.GetDirection().y;
    FillIntersectionInfo(hit1, ray);

    return collisionInfo;
}

Vec3D Plane::LocalNormalAt(const Vec3D& point) const
{
    return Vec3D(0, 1, 0);
}
