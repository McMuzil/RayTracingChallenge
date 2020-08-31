#pragma once

#include "Object.h"

class Cube : public Object
{
public:
    virtual CollisionInfo IntersectInternal(const Ray& localRay) const override;

protected:
    virtual Vec3D LocalNormalAt(const Vec3D& point) const override;

private:
    Vec2D CheckAxis(float origin, float direction) const;
};