#pragma once
#include "Material.h"
#include "Vector.h"

class Ray;
struct CollisionInfo;
struct Hit;

class Object
{
public:
    virtual ~Object() = default;

    Vec3D NormalAt(float x, float y, float z) const { return NormalAt(Vec3D(x, y, z)); }
    virtual Vec3D NormalAt(const Vec3D& point) const = 0;

    const Material& GetMaterial() const { return m_material; }
    void SetMaterial(const Material& val) { m_material = val; }

    // TODO: The object shouldn't be responsible for this logic
    virtual CollisionInfo Intersect(const Ray& ray) const = 0;

    bool operator==(const Object& other) const
    {
        return m_material == other.m_material;
    }

private:
    // TODO: This should lie in the same component as Intersect method
    virtual void FillIntersectionInfo(Hit& hit, const Object* obj, const Ray& ray) const = 0;

private:
    Material m_material;
};