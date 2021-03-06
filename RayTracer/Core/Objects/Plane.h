#pragma once

#include "Object.h"

class Plane : public Object
{
protected:
    virtual CollisionInfo IntersectInternal(const Ray& localRay) const override;
    virtual Vec3D LocalNormalAt(const Vec3D& point) const override;
};