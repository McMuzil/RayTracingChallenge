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

int main()
{
    Canvas canvas(1000, 1000);
    Vec4D color(1, 0, 0);
    Sphere sphere;
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
                canvas.SetPixel(color, x, y);
            }
        }
    }

    std::ofstream file("image.ppm");
    file << canvas.ToPPM().c_str() << std::endl;
    file.close();

    return 0;
}