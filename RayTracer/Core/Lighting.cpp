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

Vec3D Lighting::Calculate(const World& world, const Hit* hit, size_t bouncesLeft /*= Constants::BouncesCount*/)
{
    if (!hit)
    {
        return Vec3D(0.f);
    }
    assert(hit->object);

    const bool inShadow = Lighting::IsInShadow(world, hit->biasedAbove);

    const Vec3D surfaceColor = Calculate(*hit->object, world.GetLight(), hit->point, hit->toEye, hit->normal, inShadow);
    const Vec3D reflectedColor = CalculateReflectedColor(world, hit, bouncesLeft);
    const Vec3D refractedColor = CalculateRefractedColor(world, hit, bouncesLeft);

    const Material& material = hit->object->GetMaterial();
    if (material.GetReflectivity() > 0.f && material.GetTransparency() > 0.f)
    {
        const float reflectance = Shlick(*hit);
        return surfaceColor + 
            reflectedColor * reflectance + 
            refractedColor * (1.f - reflectance);
    }

    return surfaceColor + reflectedColor + refractedColor;
}

Vec3D Lighting::Calculate(const World& world, const Ray& ray, size_t bouncesLeft /*= Constants::BouncesCount*/)
{
    CollisionInfo info = world.Intersect(ray);
    Hit* hit = info.GetFirstHit();

    if (!hit)
    {
        return Vec3D(0.f);
    }

    return Calculate(world, hit, bouncesLeft);
}

Vec3D Lighting::CalculateReflectedColor(const World& world, const Hit* hit, size_t bouncesLeft /*= Constants::BouncesCount*/)
{
    assert(hit->object);
    if (bouncesLeft == 0 ||
        !hit->object ||
        Helpers::IsEqualWithEpsilon(hit->object->GetMaterial().GetReflectivity(), 0.f))
    {
        return Vec3D(0.f);
    }

    const Ray reflectedRay(hit->biasedAbove, hit->reflectedDir);

    const Vec3D reflectedColor = Calculate(world, reflectedRay, --bouncesLeft);

    return reflectedColor * hit->object->GetMaterial().GetReflectivity();
}

Vec3D Lighting::CalculateRefractedColor(const World& world, const Hit* hit, size_t bouncesLeft /*= Constants::BouncesCount*/)
{
    if (!hit || !hit->object || bouncesLeft == 0)
    {
        return Vec3D(0.f);
    }

    if (Helpers::IsEqualWithEpsilon(hit->object->GetMaterial().GetTransparency(), 0.f))
    {
        return Vec3D(0.f);
    }

    // Snell's Law
    // 
    // sin(O1)     n2
    // ------- == ----
    // sin(O2)     n1
    // 
    // Where:
    // O1 - Angle between the incoming vector and the normal
    // O2 - Angle between the outgoing vector and the reversed normal
    // n1 - Refraction index of the first media
    // n2 - Refraction index of the second media
    assert(!Helpers::IsEqualWithEpsilon(hit->refractiveIndexTo, 0.f));
    const float nRatio = hit->refractiveIndexFrom / hit->refractiveIndexTo; // n1 / n2
    const float cosIncoming = hit->toEye.Dot(hit->normal);
    const float sinRefracted = nRatio * nRatio * (1 - cosIncoming * cosIncoming);

    if (sinRefracted > 1.f)
    {
        return Vec3D(0.f);
    }

    const float cosRefracted = sqrt(1.f - sinRefracted);
    Vec3D refractedDir = hit->normal * (nRatio * cosIncoming - cosRefracted) - hit->toEye * nRatio;

    const Ray refractedRay(hit->biasedBelow, refractedDir);

    return Calculate(world, refractedRay, bouncesLeft - 1) * hit->object->GetMaterial().GetTransparency();
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

float Lighting::Shlick(const Hit& hit)
{
    float cosine = hit.toEye.Dot(hit.normal);

    if (hit.refractiveIndexFrom > hit.refractiveIndexTo)
    {
        const float nRatio = hit.refractiveIndexFrom / hit.refractiveIndexTo;
        const float sinRefracted = nRatio * nRatio * (1 - cosine * cosine);
        if (sinRefracted > 1.f)
        {
            return 1.f;
        }

        cosine = sqrt(1.f - sinRefracted);
    }

    float r0 = pow((hit.refractiveIndexFrom - hit.refractiveIndexTo) / (hit.refractiveIndexFrom + hit.refractiveIndexTo), 2);

    return r0 + (1 - r0) * pow(1.f - cosine, 5);
}
