#pragma once
#include "Vector.h"
#include "vector"

class Object;

struct CollisionInfo
{
    struct Hit
    {
        const Object* object;
        Vec3D point;
        float distance;
    };
    std::vector<Hit> hits;

    const Hit* GetFirstHit() const
    {
        const auto it = std::min_element(hits.cbegin(), hits.cend(), [](const Hit& hit1, const Hit& hit2)
        {
            return hit1.distance < hit2.distance;
        });

        if (it == hits.cend())
        {
            return nullptr;
        }

        return &(*it);
    }
};