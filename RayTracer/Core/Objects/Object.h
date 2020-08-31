#pragma once
#include "RayTracer/Core/Material.h"
#include "RayTracer/Core/Matrix.h"
#include "RayTracer/Core/Vector.h"

#include "RayTracer/Core/CollisionInfo.h"

class Ray;
struct Hit;

class Object
{
public:
    virtual ~Object();

    Vec3D NormalAt(float x, float y, float z) const { return NormalAt(Vec3D(x, y, z)); }
    virtual Vec3D NormalAt(const Vec3D& point) const;

    const Matrix<4, 4>& GetTransform() const { return m_transform; }
    void SetTransform(const Matrix<4, 4>& transform) { m_transform = transform; }

    const Material& GetMaterial() const { return m_material; }
    Material& GetMaterial() { return m_material; }
    void SetMaterial(const Material& val) { m_material = val; }

    // TODO: The object shouldn't be responsible for this logic
    CollisionInfo Intersect(const Ray& ray) const;
    virtual CollisionInfo IntersectInternal(const Ray& ray) const = 0;

    // TODO: This should lie in the same component as Intersect method
    void FillIntersectionInfo(Hit& hit, const Ray& ray, const CollisionInfo& info = CollisionInfo()) const;
    void FillRefractionIndices(Hit& hit, const CollisionInfo& info) const;

    Vec3D FromObjectSpace(const Vec3D& vec) const;
    Vec3D ToObjectSpace(const Vec3D& vec) const;

    Vec3D GetColorAt(const Vec3D& point) const;

    bool operator==(const Object& other) const
    {
        return m_material == other.m_material &&
            m_transform.IsEqualWithEpsilon(other.m_transform);
    }

protected:
    virtual Vec3D LocalNormalAt(const Vec3D& point) const = 0;
protected:
    Matrix<4, 4> m_transform = Matrix<4, 4>::Identity();
    Material m_material;
};