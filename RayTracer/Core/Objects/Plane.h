#pragma once

#include "Object.h"

class Plane : public Object
{
public:
    virtual CollisionInfo Intersect(const Ray& ray) const override;

protected:
    virtual Vec3D LocalNormalAt(const Vec3D& point) const override;
};