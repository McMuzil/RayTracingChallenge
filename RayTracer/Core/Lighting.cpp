#include "Core/Lighting.h"

#include "CollisionInfo.h"
#include "Material.h"
#include "PointLight.h"
#include "Ray.h"
#include "World.h"
#include "Pattern/Pattern.h"

Vec3D Lighting::Calculate(
    const Object& object, 
    const PointLight& light, 
    const Vec3D& point, 
    const Vec3D& toEye, 
    const Vec3D& normal, 
    bool inShadow /* bool inShadow = false */
)
{
    const Material& material = object.GetMaterial();
    const Pattern* pattern = material.GetPattern();
    const Vec3D materialColor = object.GetColorAt(point);

    Vec3D effectiveColor = materialColor * light.GetColor();
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

    if (inShadow)
    {
        return ambient;
    }
    else
    {
        return ambient + diffuse + specular;
    }
}

Vec3D Lighting::Calculate(const World& world, const Hit* hit)
{
    if (!hit)
    {
        return Vec3D(0.f);
    }
    assert(hit->object);

    const bool inShadow = Lighting::IsInShadow(world, hit->biasedPoint);

    return Calculate(*hit->object, world.GetLight(), hit->point, hit->toEye, hit->normal, inShadow);
}

Vec3D Lighting::Calculate(const World& world, const Ray& ray)
{
    CollisionInfo info = world.Intersect(ray);
    return Calculate(world, info.GetFirstHit());
}

bool Lighting::IsInShadow(const World& world, const Vec3D& point)
{
    const Vec3D toPointLight = world.GetLight().GetPosition() - point;
    const Vec3D toPointLightDir = toPointLight.Normalize();
    const float distance = toPointLight.Length();

    const Ray ray(point, toPointLightDir);
    const CollisionInfo info = world.Intersect(ray);
    const Hit* hit = info.GetFirstHit();

    return (hit && hit->distance < distance);
}
