#pragma once
#include "Vector.h"

class Material;
class PointLight;

class Lighting
{
public:

    static Vec3D Calculate(
        const Material& material,
        const PointLight& light,
        const Vec3D& point,
        const Vec3D& toEye,
        const Vec3D& normal
    );
};