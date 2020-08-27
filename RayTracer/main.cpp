#pragma once

#include <iostream>
#include <fstream>

#include "Core/Camera.h"
#include "Core/Canvas.h"
#include "Core/CollisionInfo.h"
#include "Core/Lighting.h"
#include "Core/Material.h"
#include "Core/Matrix.h"
#include "Core/Objects/Plane.h"
#include "Core/Objects/Sphere.h"
#include "Core/Pattern/StripePattern.h"
#include "Core/PointLight.h"
#include "Core/Ray.h"
#include "Core/Transform.h"
#include "Core/Vector.h"
#include "Core/World.h"
#include "Core/Pattern/CheckerPattern.h"

int main()
{
    World world;
    std::vector<std::unique_ptr<Object>>& objects = world.GetObjects();
    std::unique_ptr<Pattern> pattern = std::make_unique<CheckerPattern>(Vec3D(1.f, 1.f, 1.f), Vec3D(0.f, 0, 0));

    Plane floor;
    Material floorMat = floor.GetMaterial();
    floorMat.SetColor(Vec3D(1, 0.9f, 0.9f));
    floorMat.SetSpecular(0.f);
    floorMat.SetPattern(std::move(pattern));
    floor.SetMaterial(floorMat);
    objects.push_back(std::make_unique<Plane>(floor));

    Plane leftWall;
    leftWall.SetTransform(
        Transform::Translation(0, 0, 5) *
        Transform::RotationY(-Constants::Pi / 4.f) * Transform::RotationX(Constants::Pi / 2.f)
    );
    leftWall.SetMaterial(floorMat);
    objects.push_back(std::make_unique<Plane>(leftWall));

    Plane rightWall;
    rightWall.SetTransform(
        Transform::Translation(0, 0, 5) *
        Transform::RotationY(Constants::Pi / 4.f) * Transform::RotationX(Constants::Pi / 2.f)
    );
    rightWall.SetMaterial(floorMat);
    objects.push_back(std::make_unique<Plane>(rightWall));

    Sphere middle;
    middle.SetTransform(Transform::Translation(-0.5f, 1, 0.5f));
    Material middleMat = middle.GetMaterial();
    middleMat.SetColor(Vec3D(1.f));
    middleMat.SetDiffuse(0.0f);
    middleMat.SetSpecular(0.2f);
    middleMat.SetReflectivity(0.9f);
    middle.SetMaterial(middleMat);
    objects.push_back(std::make_unique<Sphere>(middle));

    Sphere right;
    right.SetTransform(
        Transform::Translation(1.5f, 0.5f, -0.5f) *
        Transform::Scaling(0.5f, 0.5f, 0.5f)
    );
    Material rightMat = right.GetMaterial();
    rightMat.SetColor(Vec3D(0.5f, 1, 0.1f));
    rightMat.SetDiffuse(0.7f);
    rightMat.SetSpecular(0.3f);
    right.SetMaterial(rightMat);
    objects.push_back(std::make_unique<Sphere>(right));

    Sphere left;
    left.SetTransform(
        Transform::Translation(-1.5f, 0.33f, -0.75f) *
        Transform::Scaling(0.33f, 0.33f, 0.33f)
    );
    Material leftMat = left.GetMaterial();
    leftMat.SetColor(Vec3D(1.f, 0.9f, 0.1f));
    leftMat.SetDiffuse(0.7f);
    leftMat.SetSpecular(0.3f);
    left.SetMaterial(leftMat);
    objects.push_back(std::make_unique<Sphere>(left));

    PointLight pointLight(Vec3D(-10, 10, -10), Vec3D(1, 1, 1));
    world.SetLight(pointLight);

    Camera camera(Vec2Du(320, 240), 75);
    camera.SetTransform(Transform::LookAt(Vec3D(0, 1.5f, -5), Vec3D(0, 1, 0)));

    Canvas canvas = camera.Render(world);

    std::ofstream file("image.ppm");
    file << canvas.ToPPM().c_str() << std::endl;
    file.close();

    return 0;
}