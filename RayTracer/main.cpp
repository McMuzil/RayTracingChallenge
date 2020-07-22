#pragma once

#include <iostream>
#include <fstream>

#include "Core/Vector.h"
#include "Core/Matrix.h"
#include "Core/Canvas.h"
#include "Core/Sphere.h"
#include "Core/Ray.h"
#include "Core/CollisionInfo.h"
#include "Core/Collision.h"
#include "Core/PointLight.h"
#include "Core/Lighting.h"

int main()
{
    Canvas canvas(200, 200);
    PointLight pointLight(Vec3D(-10, 10, -10), Vec3D(1, 1, 1));
    Sphere sphere;
    Material material;
    material.SetColor(Vec3D(1.f, 0.2f, 1.f));
    sphere.SetMaterial(material);
    Vec3D rayOrigin(0, 0, -5);
    float wallZ = 10.f;
    float wallSize = 7.f;
    float pixelWidth = wallSize / canvas.GetWidth();
    float pixelheight = wallSize / canvas.GetHeight();
    float half = wallSize / 2.f;

    for (size_t y = 0; y < canvas.GetHeight(); y++)
    {
        float worldY = half - pixelWidth * y;

        for (size_t x = 0; x < canvas.GetWidth(); x++)
        {
            float worldX = -half + pixelheight * x;

            Vec3D position(worldX, worldY, wallZ);

            Ray ray(rayOrigin, (position - rayOrigin).Normalize());
            CollisionInfo info = Collision::Intersect(ray, sphere);

            const CollisionInfo::Hit* hit = info.GetFirstHit();
            if (hit)
            {
                Vec3D normal = hit->object->NormalAt(hit->point);
                Vec3D toEye = -ray.GetDirection();
                Vec3D color = Lighting::Calculate(hit->object->GetMaterial(), pointLight, hit->point, toEye, normal);

                canvas.SetPixel(color, x, y);
            }
        }
    }

    std::ofstream file("image.ppm");
    file << canvas.ToPPM().c_str() << std::endl;
    file.close();

    return 0;
}