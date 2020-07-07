#pragma once

struct CollisionInfo;

class Ray;
class Sphere;

class Collision
{
public:

    static CollisionInfo Intersect(const Ray& ray, const Sphere& sphere);
};