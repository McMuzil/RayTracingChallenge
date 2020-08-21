#include "Core/CollisionInfo.h"
#include "Core/Objects/Sphere.h"
#include "Core/Transform.h"
#include "Core/World.h"

World World::CreateDefault()
{
    World w;
    w.m_pointLight = PointLight(Vec3D(-10, 10, -10), Vec3D(1, 1, 1));

    assert(w.m_objects.size() == 0);

    auto sphere1 = std::make_unique<Sphere>();
    Material material1;
    material1.SetColor(Vec3D(0.8f, 1.f, 0.6f));
    material1.SetDiffuse(0.7f);
    material1.SetSpecular(0.2f);
    sphere1->SetMaterial(material1);
    w.m_objects.emplace_back(std::move(sphere1));

    auto sphere2 = std::make_unique<Sphere>();
    sphere2->SetTransform(Transform::Scaling(Vec3D(0.5f)));
    w.m_objects.emplace_back(std::move(sphere2));

    return w;
}

bool World::Contains(const Object* object) const
{
    assert(object);
    const auto predicate = [&object](const std::unique_ptr<Object>& worldObj)
    {
        return *worldObj == *object;
    };
    return std::find_if(m_objects.cbegin(), m_objects.cend(), predicate) != GetObjects().end();
}

bool World::Contains(const Object& object) const
{
    const auto predicate = [&object](const std::unique_ptr<Object>& worldObj)
    {
        return *worldObj == object;
    };
    return std::find_if(m_objects.cbegin(), m_objects.cend(), predicate) != GetObjects().end();
}

CollisionInfo World::Intersect(const Ray& ray) const
{
    CollisionInfo worldInfo;

    for (const std::unique_ptr<Object>& object : m_objects)
    {
        CollisionInfo info = object->Intersect(ray);
        for (const Hit& hit : info.hits)
        {
            Helpers::InsertSorted(worldInfo.hits, hit);
        }
    }

    return worldInfo;
}
