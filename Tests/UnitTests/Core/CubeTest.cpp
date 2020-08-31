#include "pch.h"
#include "CppUnitTest.h"

#include "RayTracer/Core/CollisionInfo.h"
#include "RayTracer/Core/Ray.h"
#include "RayTracer/Core/Objects/Cube.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(CubeTest)
    {
    public:

        TEST_METHOD(RayIntersectsCube)
        {
            Vec3D origins[7] = {
                Vec3D( 5.f,   0.5f, 0.f),
                Vec3D(-5.f,   0.5f, 0.f),
                Vec3D( 0.5f,  5.f,  0.f),
                Vec3D( 0.5f, -5.f,  0.f),
                Vec3D( 0.5f,  0.f,  5.f),
                Vec3D( 0.5f,  0.f, -5.f),
                Vec3D( 0.f,   0.5f, 0.f),
            };
            Vec3D directions[7] = {
                Vec3D(-1.f,  0.f,  0.f),
                Vec3D( 1.f,  0.f,  0.f),
                Vec3D( 0.f, -1.f,  0.f),
                Vec3D( 0.f,  1.f,  0.f),
                Vec3D( 0.f,  0.f, -1.f),
                Vec3D( 0.f,  0.f,  1.f),
                Vec3D( 0.f,  0.f,  1.f),
            };
            float t1[7] = { 4, 4, 4, 4, 4, 4, -1 };
            float t2[7] = { 6, 6, 6, 6, 6, 6,  1 };

            Cube cube;

            for (int i = 0; i < 7; ++i)
            {
                Ray ray(origins[i], directions[i]);

                CollisionInfo info = cube.IntersectInternal(ray);

                Assert::IsTrue(info.hits.size() == 2, std::to_wstring(i).c_str());
                Assert::IsTrue(info.hits[0].distance == t1[i], std::to_wstring(i).c_str());
                Assert::IsTrue(info.hits[1].distance == t2[i], std::to_wstring(i).c_str());
            }
        }

        TEST_METHOD(RayMissesCube)
        {
            Vec3D origins[6] = {
                Vec3D(-2,  0,  0),
                Vec3D( 0, -2,  0),
                Vec3D( 0,  0, -2),
                Vec3D( 2,  0,  2),
                Vec3D( 0,  2,  2),
                Vec3D( 2,  2,  0),
            };

            Vec3D directions[6] = {
                Vec3D(0.2673f, 0.5345f, 0.8018f),
                Vec3D(0.8018f, 0.2673f, 0.5345f),
                Vec3D(0.5345f, 0.8018f, 0.2673f),
                Vec3D(   0,       0,      -1   ),
                Vec3D(   0,      -1,       0   ),
                Vec3D(  -1,       0,       0   ),
            };

            Cube cube;

            for (int i = 0; i < 6; ++i)
            {
                Ray ray(origins[i], directions[i]);

                CollisionInfo info = cube.IntersectInternal(ray);

                Assert::IsTrue(info.hits.size() == 0, std::to_wstring(i).c_str());
            }
        }

        TEST_METHOD(NormalOnCube)
        {
            Vec3D points[8] = {
                Vec3D(1, 0.5f, -0.8f),
                Vec3D(-1, -0.2f, 0.9f),
                Vec3D(-0.4f, 1, -0.1f),
                Vec3D(0.3f, -1, -0.7f),
                Vec3D(-0.6f, 0.3f, 1),
                Vec3D(0.4f, 0.4f, -1),
                Vec3D(1, 1, 1),
                Vec3D(-1, -1, -1),
            };

            Vec3D normals[8] = {
                Vec3D(1, 0, 0) ,
                Vec3D(-1, 0, 0),
                Vec3D(0, 1, 0) ,
                Vec3D(0, -1, 0),
                Vec3D(0, 0, 1) ,
                Vec3D(0, 0, -1),
                Vec3D(1, 0, 0) ,
                Vec3D(-1, 0, 0),
            };

            Cube cube;

            for (size_t i = 0; i < 8; i++)
            {
                Vec3D normal = cube.NormalAt(points[i]);

                Assert::IsTrue(normal.IsEqualWithEpsilon(normals[i]), std::to_wstring(i).c_str());
            }
        }
    };
}
