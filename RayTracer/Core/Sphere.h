#pragma once
#include "Object.h"

class Sphere : public Object
{
public:

    const Vec4D& GetPosition() const { return m_position; }
    Vec4D& GetPosition() { return m_position; }

private:

    Vec4D m_position = Vec4D(0, 0, 0, 1);
};