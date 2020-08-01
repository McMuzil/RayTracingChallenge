#pragma once

#include "Material.h"
#include "Matrix.h"
#include "Object.h"
#include "Vector.h"

class Sphere : public Object
{
public:

    const Matrix<4, 4>& GetTransform() const { return m_transform; }
    void SetTransform(const Matrix<4, 4>& transform) { m_transform = transform; }

    using Object::NormalAt;
    Vec3D NormalAt(const Vec3D& point) const override;

    CollisionInfo Intersect(const Ray& ray) const override;

    bool operator==(const Sphere& other) const
    {
        return Object::operator==(other) &&
            m_transform.IsEqualWithEpsilon(other.m_transform);
    }

private:
    // This should lie in the same component as Intersect method
    void FillIntersectionInfo(Hit& hit, const Object* obj, const Ray& ray) const override;

private:
    Matrix<4, 4> m_transform = Matrix<4, 4>::Identity();
};