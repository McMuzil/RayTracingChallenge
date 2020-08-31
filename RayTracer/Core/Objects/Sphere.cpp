#include "RayTracer/Core/Objects/Sphere.h"

#include "RayTracer/Core/Ray.h"
#include "RayTracer/Core/CollisionInfo.h"

CollisionInfo Sphere::IntersectInternal(const Ray& ray) const
{
    const Ray rayInv = ray.Transform(GetTransform().Inverse());
    const Vec3D sphereToRay = rayInv.GetOrigin();

    const float a = rayInv.GetDirection().Dot(rayInv.GetDirection());
    const float b = 2.f * rayInv.GetDirection().Dot(sphereToRay);
    const float c = sphereToRay.Dot(sphereToRay) - 1.f;

    const float discriminant = b * b - 4 * a * c;

    if (discriminant < 0.f)
    {
        return CollisionInfo();
    }
    else if (Helpers::IsEqualWithEpsilon(discriminant, 0.f))
    {
        CollisionInfo collisionInfo;

        Hit& hit = collisionInfo.hits.emplace_back();
        hit.distance = -b / (2.f * a);
        FillIntersectionInfo(hit, ray);

        return collisionInfo;
    }
    else
    {
        CollisionInfo collisionInfo;

        Hit& hit1 = collisionInfo.hits.emplace_back();
        hit1.distance = (-b - sqrt(discriminant)) / (2.f * a);
        FillIntersectionInfo(hit1, ray);

        Hit& hit2 = collisionInfo.hits.emplace_back();
        hit2.distance = (-b + sqrt(discriminant)) / (2.f * a);
        FillIntersectionInfo(hit2, ray);

        return collisionInfo;
    }
}

Vec3D Sphere::LocalNormalAt(const Vec3D& localPoint) const
{
    return localPoint;
}
