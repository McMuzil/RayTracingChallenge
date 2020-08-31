#pragma once

#include "RayTracer/Core/Objects/Object.h"

class Sphere : public Object
{
protected:
    CollisionInfo IntersectInternal(const Ray& ray) const override;
    Vec3D LocalNormalAt(const Vec3D& localPoint) const override;
};