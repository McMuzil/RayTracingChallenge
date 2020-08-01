#include "Core/Lighting.h"

#include "CollisionInfo.h"
#include "Material.h"
#include "PointLight.h"
#include "Ray.h"
#include "World.h"

Vec3D Lighting::Calculate(const Material& material, const PointLight& light, const Vec3D& point, const Vec3D& toEye, const Vec3D& normal)
{
    Vec3D effectiveColor = material.GetColor() * light.GetColor();
    Vec3D toLight = (light.GetPosition() - point).Normalize();
    Vec3D ambient = effectiveColor * material.GetAmbient();

    float lightDotNormal = toLight.Dot(normal);

    Vec3D diffuse(0.f);
    Vec3D specular(0.f);

    if (lightDotNormal >= 0.f)
    {
        diffuse = effectiveColor * material.GetDiffuse() * lightDotNormal;
        Vec3D reflect = Vec3D::Reflect(-toLight, normal);
        float reflectDotEye = reflect.Dot(toEye);

        if (reflectDotEye > 0.f)
        {
            float factor = pow(reflectDotEye, material.GetShininess());
            specular = light.GetColor() * material.GetSpecular() * factor;
        }
    }

    return ambient + diffuse + specular;
}

Vec3D Lighting::Calculate(const World& world, const Hit* hit)
{
    if (!hit)
    {
        return Vec3D(0.f);
    }

    return Calculate(hit->object->GetMaterial(), world.GetLight(), hit->point, hit->toEye, hit->normal);
}

Vec3D Lighting::Calculate(const World& world, const Ray& ray)
{
    CollisionInfo info = world.Intersect(ray);
    return Calculate(world, info.GetFirstHit());
}
