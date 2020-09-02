#include "RayTracer/Core/Objects/Group.h"

CollisionInfo Group::IntersectInternal(const Ray& localRay) const
{
    CollisionInfo info;

    for (const Object* child : m_children)
    {
        CollisionInfo childInfo = child->Intersect(localRay);

        for (const Hit& hit : childInfo.hits)
        {
            Helpers::InsertSorted(info.hits, hit);
        }
    }

    return info;
}

void Group::AddChild(Object* object)
{
    if (std::find(m_children.cbegin(), m_children.cend(), object) != m_children.cend())
    {
        assert(!"The given object is already a child of the group.");
        return;
    }

    assert(!object->GetParent());
    object->SetParent(this);

    m_children.emplace_back(object);
}

Vec3D Group::LocalNormalAt(const Vec3D& point) const
{

    return Vec3D(0.f);
}
