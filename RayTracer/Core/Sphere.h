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

    Vec3D NormalAt(float x, float y, float z) const { return NormalAt(Vec3D(x, y, z)); }
    Vec3D NormalAt(const Vec3D& point) const;

    const Material& GetMaterial() const { return m_material; }
    void SetMaterial(const Material& val) { m_material = val; }

private:

    Matrix<4, 4> m_transform = Matrix<4, 4>::Identity();
    Material m_material;
};