#pragma once
#include "Vector.h"
#include "vector"

class Object;

struct Hit
{
    Hit() = default;

    Hit(float distance)
        : Hit(distance, nullptr)
    {
    }

    Hit(float distance, const Object* object)
        : distance(distance)
        , object(object)
    {
    }

    const Object* object = nullptr;
    Vec3D point;
    Vec3D biasedAbove;
    Vec3D biasedBelow;
    Vec3D normal;
    Vec3D toEye;
    Vec3D reflectedDir;
    float distance = 0.f;
    float refractiveIndexFrom = 1.f;
    float refractiveIndexTo = 1.f;
    bool inside = false;

    bool operator<(const Hit& other) const
    {
        return distance < other.distance;
    }
};

struct CollisionInfo
{
    std::vector<Hit> hits;

    Hit* GetFirstHit() { return const_cast<Hit*>(const_cast<const CollisionInfo*>(this)->GetFirstHit()); }

    const Hit* GetFirstHit() const
    {
        auto it = std::find_if(hits.begin(), hits.end(), [](const Hit& hit)
        {
            return hit.distance >= 0.f;
        });

        return it != hits.cend() ? &(*it) : nullptr;
    }
};