#pragma once
#include "RayTracer/Core/Objects/Object.h"
#include "PointLight.h"
#include "vector"

struct CollisionInfo;

class World
{
public:

    static World CreateDefault();

    const PointLight& GetLight() const { return m_pointLight; }
    void SetLight(const PointLight& val) { m_pointLight = val; }

    bool Contains(const Object& object) const;
    bool Contains(const Object* object) const;

    using ObjectsVector = std::vector<std::unique_ptr<Object>>;
    ObjectsVector& GetObjects() { return m_objects; }
    const ObjectsVector& GetObjects() const { return m_objects; }

    CollisionInfo Intersect(const Ray& ray) const;

private:
    // TODO: we should be able to have more than one light
    // TODO: we should store a generic Light class instead of PointLight
    PointLight m_pointLight;

    // TODO: change the structure to Tree
    std::vector<std::unique_ptr<Object>> m_objects;
};