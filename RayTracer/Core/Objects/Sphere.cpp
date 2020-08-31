#include "RayTracer/Core/Objects/Sphere.h"

#include "RayTracer/Core/Ray.h"
#include "RayTracer/Core/CollisionInfo.h"

CollisionInfo Sphere::IntersectInternal(const Ray& localRay) const
{
    const Vec3D sphereToRay = localRay.GetOrigin();

    const float a = localRay.GetDirection().Dot(localRay.GetDirection());
    const float b = 2.f * localRay.GetDirection().Dot(sphereToRay);
    const float c = sphereToRay.Dot(sphereToRay) - 1.f;

    const float discriminant = b * b - 4 * a * c;

    if (discriminant < 0.f)
    {
        return CollisionInfo();
    }
    
    const Ray ray = localRay.Transform(GetTransform());

    if (Helpers::IsEqualWithEpsilon(discriminant, 0.f))
    {
        CollisionInfo collisionInfo;

        const float distance = -b / (2.f * a);
        Hit& hit = collisionInfo.hits.emplace_back(distance, this);

        return collisionInfo;
    }
    else
    {
        CollisionInfo collisionInfo;

        const float distance1 = (-b - sqrt(discriminant)) / (2.f * a);
        Hit& hit1 = collisionInfo.hits.emplace_back(distance1, this);

        const float distance2 = (-b + sqrt(discriminant)) / (2.f * a);
        Hit& hit2 = collisionInfo.hits.emplace_back(distance2, this);

        return collisionInfo;
    }
}

Vec3D Sphere::LocalNormalAt(const Vec3D& localPoint) const
{
    return localPoint;
}
