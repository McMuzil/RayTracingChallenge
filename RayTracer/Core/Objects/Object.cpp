#include "RayTracer/Core/Objects/Object.h"

#include "RayTracer/Core/CollisionInfo.h"
#include "RayTracer/Core/Pattern/Pattern.h"
#include "RayTracer/Core/Ray.h"

Object::~Object()
{

}

Vec3D Object::NormalAt(const Vec3D& point) const
{
    const Vec3D pointObjSpace = ToObjectSpace(point);
    const Vec3D normalObjSpace = LocalNormalAt(pointObjSpace);
    const Vec3D normalWorldSpace = ToWorldSpace(normalObjSpace);

    return normalWorldSpace.Normalize();
}

Vec3D Object::ToWorldSpace(const Vec3D& vec) const
{
    Vec3D localPoint = m_transform.Inverse().Transpose() * vec.AsPoint();

    if (m_parent)
    {
        localPoint = m_parent->ToWorldSpace(localPoint);
    }

    return localPoint;
}

Vec3D Object::ToObjectSpace(const Vec3D& vec) const
{
    Vec3D localPoint = vec;

    if (m_parent)
    {
        localPoint = m_parent->ToObjectSpace(vec);
    }

    return m_transform.Inverse() * localPoint.AsPoint();
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
        assert(hit->object);
        hit->object->FillIntersectionInfo(*hit, ray, info);
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
