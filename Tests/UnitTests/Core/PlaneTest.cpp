#include "pch.h"
#include "CppUnitTest.h"

#include "Core\Objects\Plane.h"
#include "Core\Ray.h"
#include "Core\CollisionInfo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(PlaneTest)
    {
    public:

        TEST_METHOD(NormalOfPlane)
        {
            const std::unique_ptr<Object> plane = std::make_unique<Plane>();

            Vec3D normal1 = plane->NormalAt(Vec3D(0.f));
            Vec3D normal2 = plane->NormalAt(Vec3D(10, 0, -10));
            Vec3D normal3 = plane->NormalAt(Vec3D(-5.f, 0, 150));
            Vec3D expectedResult = Vec3D(0, 1, 0);

            Assert::IsTrue(expectedResult.IsEqualWithEpsilon(normal1));
            Assert::IsTrue(expectedResult.IsEqualWithEpsilon(normal2));
            Assert::IsTrue(expectedResult.IsEqualWithEpsilon(normal3));
        }

        TEST_METHOD(IntersectParallelRay)
        {
            const std::unique_ptr<Object> plane = std::make_unique<Plane>();
            Ray ray(Vec3D(0, 10, 0), Vec3D(0, 0, 1));

            CollisionInfo info = plane->Intersect(ray);

            Assert::IsNull(info.GetFirstHit());
        }

        TEST_METHOD(IntersectCoplanarRay)
        {
            const std::unique_ptr<Object> plane = std::make_unique<Plane>();
            Ray ray(Vec3D(0, 0, 0), Vec3D(0, 0, 1));

            CollisionInfo info = plane->Intersect(ray);

            Assert::IsNull(info.GetFirstHit());
        }

        TEST_METHOD(IntersectRayAbove)
        {
            const std::unique_ptr<Object> plane = std::make_unique<Plane>();
            Ray ray(Vec3D(0, 1, 0), Vec3D(0, -1, 0));

            CollisionInfo info = plane->Intersect(ray);

            Assert::AreEqual(1, int(info.hits.size()));
            Assert::IsTrue(plane.get() == info.GetFirstHit()->object);
        }

        TEST_METHOD(IntersectRayBelow)
        {
            const std::unique_ptr<Object> plane = std::make_unique<Plane>();
            Ray ray(Vec3D(0, -1, 0), Vec3D(0, 1, 0));

            CollisionInfo info = plane->Intersect(ray);

            Assert::AreEqual(1, int(info.hits.size()));
            Assert::IsTrue(plane.get() == info.GetFirstHit()->object);
        }
    };
}
