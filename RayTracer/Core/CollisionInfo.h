#pragma once
#include "Vector.h"
#include "vector"

class Object;

struct Hit
{
    const Object* object = nullptr;
    Vec3D point;
    Vec3D biasedPoint;
    Vec3D normal;
    Vec3D toEye;
    float distance = 0.f;
    bool inside = false;

    bool operator<(const Hit& other) const
    {
        return distance < other.distance;
    }
};

struct CollisionInfo
{
    std::vector<Hit> hits;

    const Hit* GetFirstHit() const
    {
        const auto it = std::find_if(hits.cbegin(), hits.cend(), [](const Hit& hit)
        {
            return hit.distance >= 0.f;
        });

        return it != hits.cend() ? &(*it) : nullptr;
    }
};