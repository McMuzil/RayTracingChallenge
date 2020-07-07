#pragma once
#include "Object.h"

class Sphere : public Object
{
public:

    const Vec3D& GetPosition() const { return m_position; }
    Vec3D& GetPosition() { return m_position; }

private:

    Vec3D m_position;
};