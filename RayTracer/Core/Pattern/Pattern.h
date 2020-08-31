#pragma once
#include <vector>
#include "RayTracer/Core/ICloneable.h"
#include "RayTracer/Core/Matrix.h"
#include "RayTracer/Core/Vector.h"

class Pattern : public ICloneable
{
public:

    Pattern(const Vec3D& colorA, const Vec3D& colorB)
        : m_colors{ colorA, colorB }
    {
    }
    ~Pattern();

    Vec3D GetColor(size_t index) const { assert(index < m_colors.size()); return m_colors[index]; }
    size_t GetColorCount() const { return m_colors.size(); }

    Vec3D GetColorAt(float x, float y, float z) { return GetColorAt(Vec3D(x, y, z)); }
    virtual Vec3D GetColorAt(const Vec3D& position) const = 0;

    const Matrix<4, 4>& GetTransform() const { return m_transform; }
    void SetTransform(const Matrix<4, 4>& val) { m_transform = val; }

private:
    Pattern();

    std::vector<Vec3D> m_colors;
    Matrix<4, 4> m_transform = Matrix<4, 4>::Identity();
};
