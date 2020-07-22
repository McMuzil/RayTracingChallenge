#pragma once
#include "Material.h"
#include "Vector.h"

class Object
{
public:
    virtual ~Object() = default;

    Vec3D NormalAt(float x, float y, float z) const { return NormalAt(Vec3D(x, y, z)); }
    virtual Vec3D NormalAt(const Vec3D& point) const = 0;

    const Material& GetMaterial() const { return m_material; }
    void SetMaterial(const Material& val) { m_material = val; }

private:
    Material m_material;
};