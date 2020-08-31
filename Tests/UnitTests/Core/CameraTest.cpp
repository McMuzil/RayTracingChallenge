#include "pch.h"
#include "CppUnitTest.h"

#include "RayTracer/Core/Camera.h"
#include "RayTracer/Core/Matrix.h"
#include "RayTracer/Core/Ray.h"
#include "RayTracer/Core/Transform.h"
#include "RayTracer/Core/Canvas.h"
#include "RayTracer/Core/World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(CameraTest)
    {
    public:

        TEST_METHOD(Constructor)
        {
            const Vec2Du size(160, 120);
            float fov(90.f);
            const Camera camera(size, fov);

            Assert::IsTrue(camera.GetSize().IsEqualWithEpsilon(size));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(camera.GetFOV(), fov));
            Assert::IsTrue(camera.GetTransform().IsEqualWithEpsilon(Matrix<4, 4>::Identity()));
        }

        TEST_METHOD(PixelSizeForHorizontalCanvas)
        {
            const Camera camera(Vec2Du(200, 125), 90.f);

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(camera.GetPixelSize(), 0.01f), L"Pixel size is not correct.");
        }

        TEST_METHOD(PixelSizeForVerticalCanvas)
        {
            const Camera camera(Vec2Du(125, 200), 90.f);

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(camera.GetPixelSize(), 0.01f), L"Pixel size is not correct.");
        }

        TEST_METHOD(RayThroughCanvasCenter)
        {
            Camera camera(Vec2Du(201, 101));
            Ray ray = camera.Raycast(Vec2Du(100, 50));
            
            Assert::IsTrue(Vec3D(0.f).IsEqualWithEpsilon(ray.GetOrigin()), L"origin is not correct.");
            Assert::IsTrue(Vec3D(0.f, 0.f, -1.f).IsEqualWithEpsilon(ray.GetDirection()), L"Direction is not correct.");
        }

        TEST_METHOD(RayThroughCanvasCorner)
        {
            Camera camera(Vec2Du(201, 101));
            Ray ray = camera.Raycast(Vec2Du(0, 0));

            Assert::IsTrue(Vec3D(0.f).IsEqualWithEpsilon(ray.GetOrigin()), L"origin is not correct.");
            Assert::IsTrue(Vec3D(0.66519f, 0.33259f, -0.66851f).IsEqualWithEpsilon(ray.GetDirection()), L"Direction is not correct.");
        }

        TEST_METHOD(RayWhenCameraIsTransformed)
        {
            Camera camera(Vec2Du(201, 101));
            camera.SetTransform(Transform::RotationY(Constants::Pi / 4.f) * Transform::Translation(0, -2, 5));
            Ray ray = camera.Raycast(Vec2Du(100, 50));

            float f = sqrt(2.f) / 2.f;
            Assert::IsTrue(Vec3D(0, 2, -5).IsEqualWithEpsilon(ray.GetOrigin()), L"origin is not correct.");
            Assert::IsTrue(Vec3D(f, 0.f, -f).IsEqualWithEpsilon(ray.GetDirection()), L"Direction is not correct.");
        }

        TEST_METHOD(RenderWorld)
        {
            World world = World::CreateDefault();
            Camera camera(Vec2Du(11, 11), 90.f);
            camera.SetTransform(Transform::LookAt(Vec3D(0, 0, -5), Vec3D(0, 0, 0), Vec3D(0, 1, 0)));

            Canvas image = camera.Render(world);
            
            Assert::IsTrue(image.GetPixel(5, 5).IsEqualWithEpsilon(Vec3D(0.38066f, 0.47583f, 0.2855f)), L"Incorrect pixel's color.");

        }
    };
}
