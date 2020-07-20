#pragma once
#include "Vector.h"

class PointLight
{
public:

    PointLight(const Vec3D& position, const Vec3D& color)
        : m_position(position)
        , m_color(color)
    {
    }

    const Vec3D& GetPosition() const { return m_position; }
    void GetPosition(const Vec3D& val) { m_position = val; }

    const Vec3D& GetColor() const { return m_color; }
    void GetColor(const Vec3D& val) { m_color = val; }

private:

    Vec3D m_position;
    Vec3D m_color;
};