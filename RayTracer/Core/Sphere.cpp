#include "Core/Sphere.h"

#include "Core/Ray.h"
#include "Core/CollisionInfo.h"

Vec3D Sphere::NormalAt(const Vec3D& point) const
{
    const Matrix<4, 4> inverseTrans = GetTransform().Inverse();
    const Vec3D pointObjSpace = inverseTrans * point.AsPoint();
    const Vec3D normalObjSpace = pointObjSpace - Vec3D(0.f); // We assume that the sphere is always at (0.0.0) position
    const Vec3D normalWorldSpace = inverseTrans.Transpose() * normalObjSpace.AsPoint();

    return normalWorldSpace.Normalize();
}

CollisionInfo Sphere::Intersect(const Ray& ray) const
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
        hit.point = ray.GetPointAtDistance(hit.distance);
        FillIntersectionInfo(hit, this, ray);

        return collisionInfo;
    }
    else
    {
        CollisionInfo collisionInfo;

        Hit& hit1 = collisionInfo.hits.emplace_back();
        hit1.distance = (-b - sqrt(discriminant)) / (2.f * a);
        hit1.point = ray.GetPointAtDistance(hit1.distance);
        FillIntersectionInfo(hit1, this, ray);

        Hit& hit2 = collisionInfo.hits.emplace_back();
        hit2.distance = (-b + sqrt(discriminant)) / (2.f * a);
        hit2.point = ray.GetPointAtDistance(hit2.distance);
        FillIntersectionInfo(hit2, this, ray);

        return collisionInfo;
    }
}

void Sphere::FillIntersectionInfo(Hit& hit, const Object* obj, const Ray& ray) const
{
    hit.object = this;
    hit.toEye = -ray.GetDirection();
    hit.normal = NormalAt(hit.point);
    if (hit.toEye.Dot(hit.normal) < 0.f)
    {
        hit.inside = true;
        hit.normal = -hit.normal;
    }
    hit.biasedPoint = hit.point + hit.normal * Constants::ShadowBias;
}
