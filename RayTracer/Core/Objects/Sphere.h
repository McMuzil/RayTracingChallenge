#pragma once

#include "Core/Objects/Object.h"

class Sphere : public Object
{
public:
    CollisionInfo Intersect(const Ray& ray) const override;

protected:
    Vec3D LocalNormalAt(const Vec3D& localPoint) const override;
};