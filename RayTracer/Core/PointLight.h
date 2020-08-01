#pragma once
#include "Vector.h"

class PointLight
{
public:

    PointLight() = default;

    PointLight(const Vec3D& position, const Vec3D& color)
        : m_position(position)
        , m_color(color)
    {
    }

    const Vec3D& GetPosition() const { return m_position; }
    void SetPosition(const Vec3D& val) { m_position = val; }

    const Vec3D& GetColor() const { return m_color; }
    void SetColor(const Vec3D& val) { m_color = val; }

    bool operator==(const PointLight& other) const
    {
        return m_position.IsEqualWithEpsilon(other.m_position) &&
            m_color.IsEqualWithEpsilon(other.m_color);
    }

private:

    Vec3D m_position;
    Vec3D m_color;
};