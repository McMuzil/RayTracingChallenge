#pragma once
#include "Vector.h"
#include "vector"

class Object;

struct CollisionInfo
{
    struct Hit
    {
        const Object* object;
        Vec4D point;
        float distance;
    };
    std::vector<Hit> hits;
};