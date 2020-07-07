#include "Core/Collision.h"
#include "Core/CollisionInfo.h"
#include "Core/Ray.h"
#include "Core/Sphere.h"

CollisionInfo Collision::Intersect(const Ray& ray, const Sphere& sphere)
{
    Vec4D sphereToRay = ray.GetOrigin() - sphere.GetPosition();

    const float a = ray.GetDirection().Dot(ray.GetDirection());
    const float b = 2.f * ray.GetDirection().Dot(sphereToRay);
    const float c = sphereToRay.Dot(sphereToRay) - 1.f;

    const float discriminant = b * b - 4 * a * c;

    if (discriminant < 0.f)
    {
        return CollisionInfo();
    }
    else if (Helpers::IsEqualWithEpsilon(discriminant, 0.f))
    {
        CollisionInfo collisionInfo;

        CollisionInfo::Hit& hit = collisionInfo.hits.emplace_back();
        hit.distance = -b / (2.f * a);
        hit.point = ray.GetPointAtDistance(hit.distance);
        hit.object = &sphere;

        return collisionInfo;
    }
    else
    {
        CollisionInfo collisionInfo;

        CollisionInfo::Hit& hit1 = collisionInfo.hits.emplace_back();
        hit1.distance = (-b - sqrt(discriminant)) / (2.f * a);
        hit1.point = ray.GetPointAtDistance(hit1.distance);
        hit1.object = &sphere;

        CollisionInfo::Hit& hit2 = collisionInfo.hits.emplace_back();
        hit2.distance = (-b + sqrt(discriminant)) / (2.f * a);
        hit2.point = ray.GetPointAtDistance(hit2.distance);
        hit2.object = &sphere;

        return collisionInfo;
    }
}