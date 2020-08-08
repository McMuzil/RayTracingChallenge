#pragma once

#include <iostream>
#include <fstream>

#include "Core/Camera.h"
#include "Core/Canvas.h"
#include "Core/CollisionInfo.h"
#include "Core/Lighting.h"
#include "Core/Material.h"
#include "Core/Matrix.h"
#include "Core/PointLight.h"
#include "Core/Ray.h"
#include "Core/Sphere.h"
#include "Core/Transform.h"
#include "Core/Vector.h"
#include "Core/World.h"

int main()
{
    World world;
    std::vector<std::unique_ptr<Object>>& objects = world.GetObjects();

    Sphere floor;
    floor.SetTransform(Transform::Scaling(10, 0.01f, 10));
    Material floorMat = floor.GetMaterial();
    floorMat.SetColor(Vec3D(1, 0.9f, 0.9f));
    floorMat.SetSpecular(0.f);
    floor.SetMaterial(floorMat);
    objects.push_back(std::make_unique<Sphere>(floor));

    Sphere leftWall;
    leftWall.SetTransform(
        Transform::Translation(0, 0, 5) *
        Transform::RotationY(-Constants::Pi / 4.f) * Transform::RotationX(Constants::Pi / 2.f) *
        Transform::Scaling(10, 0.01f, 10)
    );
    leftWall.SetMaterial(floorMat);
    objects.push_back(std::make_unique<Sphere>(leftWall));

    Sphere rightWall;
    rightWall.SetTransform(
        Transform::Translation(0, 0, 5) *
        Transform::RotationY(Constants::Pi / 4.f) * Transform::RotationX(Constants::Pi / 2.f) *
        Transform::Scaling(10, 0.01f, 10)
    );
    rightWall.SetMaterial(floorMat);
    objects.push_back(std::make_unique<Sphere>(rightWall));

    Sphere middle;
    middle.SetTransform(Transform::Translation(-0.5f, 1, 0.5f));
    Material middleMat = middle.GetMaterial();
    middleMat.SetColor(Vec3D(0.1f, 1, 0.5f));
    middleMat.SetDiffuse(0.7f);
    middleMat.SetSpecular(0.3f);
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

    Camera camera(Vec2Du(720, 480), 75);
    camera.SetTransform(Transform::LookAt(Vec3D(0, 1.5f, -5), Vec3D(0, 1, 0)));

    Canvas canvas = camera.Render(world);

    std::ofstream file("image.ppm");
    file << canvas.ToPPM().c_str() << std::endl;
    file.close();

    return 0;
}