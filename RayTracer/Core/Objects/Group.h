#pragma once
#include "RayTracer/Core/Objects/Object.h"

class Group : public Object
{
public:
    virtual CollisionInfo IntersectInternal(const Ray& localRay) const override;

    void AddChild(Object* object);
    const std::vector<Object*>& GetChildren() const { return m_children; }

protected:
    virtual Vec3D LocalNormalAt(const Vec3D& point) const override;

protected:
    std::vector<Object*> m_children;
};