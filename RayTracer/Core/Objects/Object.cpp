#include "Core/Objects/Object.h"

#include "Core/CollisionInfo.h"
#include "Core/Pattern/Pattern.h"
#include "Core/Ray.h"

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

void Object::FillIntersectionInfo(Hit& hit, const Object* obj, const Ray& ray) const
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
