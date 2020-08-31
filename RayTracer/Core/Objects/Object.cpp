#include "RayTracer/Core/Objects/Object.h"

#include "RayTracer/Core/CollisionInfo.h"
#include "RayTracer/Core/Pattern/Pattern.h"
#include "RayTracer/Core/Ray.h"

Object::~Object()
{

}

Vec3D Object::NormalAt(const Vec3D& point) const
{
    const Matrix<4, 4> inverseTrans = GetTransform().Inverse();
    const Vec3D pointObjSpace = inverseTrans * point.AsPoint();
    const Vec3D normalObjSpace = LocalNormalAt(pointObjSpace);
    const Vec3D normalWorldSpace = inverseTrans.Transpose() * normalObjSpace.AsPoint();

    return normalWorldSpace.Normalize();
}

Vec3D Object::FromObjectSpace(const Vec3D& vec) const
{
    return m_transform * vec.AsPoint();
}

Vec3D Object::ToObjectSpace(const Vec3D& vec) const
{
    return m_transform.Inverse() * vec.AsPoint();
}

Vec3D Object::GetColorAt(const Vec3D& point) const
{
    Vec3D materialColor = m_material.GetColor();
    if (const Pattern* pattern = m_material.GetPattern())
    {
        const Vec3D& objectPoint = ToObjectSpace(point);
        const Vec3D& patternPoint = pattern->GetTransform().Inverse() * objectPoint.AsPoint();
        materialColor = pattern->GetColorAt(patternPoint);
    }
    return materialColor;
}

CollisionInfo Object::Intersect(const Ray& ray) const
{
    const Ray rayInv = ray.Transform(GetTransform().Inverse());

    CollisionInfo info = IntersectInternal(rayInv);

    Hit* hit = info.GetFirstHit();
    if (hit)
    {
        FillIntersectionInfo(*hit, ray, info);
    }

    return info;
}

void Object::FillIntersectionInfo(Hit& hit, const Ray& ray, const CollisionInfo& info /*= CollisionInfo()*/) const
{
    hit.point = ray.GetPointAtDistance(hit.distance);
    hit.object = this;
    hit.toEye = -ray.GetDirection();
    hit.normal = NormalAt(hit.point);
    if (hit.toEye.Dot(hit.normal) < 0.f)
    {
        hit.inside = true;
        hit.normal = -hit.normal;
    }
    hit.biasedAbove = hit.point + hit.normal * Constants::BiasAbove;
    hit.biasedBelow = hit.point - hit.normal * Constants::BiasBelow;
    hit.reflectedDir = Vec3D::Reflect(ray.GetDirection(), hit.normal);
    hit.refractiveIndexFrom = 1.f;
    hit.refractiveIndexTo = GetMaterial().GetRefractiveIndex();
    FillRefractionIndices(hit, info);
}

void Object::FillRefractionIndices(Hit& hit, const CollisionInfo& info) const
{
    if (info.hits.empty())
    {
        return;
    }

    std::vector<const Object*> containerObjects;
    for (const Hit& iHit : info.hits)
    {
        if (&iHit == &hit)
        {
            hit.refractiveIndexFrom = containerObjects.empty() ? 1.f : containerObjects[containerObjects.size() - 1]->GetMaterial().GetRefractiveIndex();
        }

        auto it = std::find(containerObjects.begin(), containerObjects.end(), iHit.object);
        if (it != containerObjects.cend())
        {
            containerObjects.erase(it);
        }
        else
        {
            containerObjects.emplace_back(iHit.object);
        }

        if (&iHit == &hit)
        {
            hit.refractiveIndexTo = containerObjects.empty() ? 1.f : containerObjects[containerObjects.size() - 1]->GetMaterial().GetRefractiveIndex();
            break;
        }
    }
}
