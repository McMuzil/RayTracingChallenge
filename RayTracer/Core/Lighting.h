#pragma once
#include "Constants.h"
#include "Vector.h"

class Material;
class Object;
class PointLight;
class Ray;
class World;
struct CollisionInfo;
struct Hit;

class Lighting
{
public:

    static Vec3D Calculate(
        const Object& object,
        const PointLight& light,
        const Vec3D& point,
        const Vec3D& toEye,
        const Vec3D& normal,
        bool inShadow = false
    );

    static Vec3D CalculateReflectedColor(const World& world, const Hit* hit, size_t bouncesLeft = Constants::BouncesCount);
    static Vec3D CalculateRefractedColor(const World& world, const Hit* hit, size_t bouncesLeft = Constants::BouncesCount);

    static Vec3D Calculate(const World& world, const Hit* hit, size_t bouncesLeft = Constants::BouncesCount);
    static Vec3D Calculate(const World& world, const Ray& ray, size_t bouncesLeft = Constants::BouncesCount);

    // TODO: we may want to calculate the float instead of bool
    static bool IsInShadow(const World& world, const Vec3D& point);

    static float Shlick(const Hit& hit);
};