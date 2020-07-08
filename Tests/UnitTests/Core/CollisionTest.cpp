#include "pch.h"
#include "CppUnitTest.h"

#include "Core/Collision.h"
#include "Core/CollisionInfo.h"
#include "Core/Ray.h"
#include "Core/Sphere.h"
#include "Core/Transform.h"
#include <Core/Helpers.h>
#include <Core/Vector.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(CollisionTest)
    {
    public:

        TEST_METHOD(RaySphereIntersectionFull)
        {
            Ray ray(Vec3D(0, 0, -5), Vec3D(0, 0, 1));
            Sphere sphere;

            CollisionInfo info = Collision::Intersect(ray, sphere);

            Assert::AreEqual(2, int(info.hits.size()));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(4.f, info.hits[0].distance));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(6.f, info.hits[1].distance));
            Assert::IsTrue(dynamic_cast<const Sphere*>(info.hits[0].object) != nullptr);
            Assert::IsTrue(dynamic_cast<const Sphere*>(info.hits[1].object) != nullptr);
            Assert::IsTrue(&sphere == info.hits[0].object);
            Assert::IsTrue(&sphere == info.hits[1].object);
        }

        TEST_METHOD(RaySphereIntersectionTangent)
        {
            Ray ray(Vec3D(0, 1, -5), Vec3D(0, 0, 1));
            Sphere sphere;

            CollisionInfo info = Collision::Intersect(ray, sphere);

            Assert::AreEqual(1, int(info.hits.size()));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(5.f, info.hits[0].distance));
        }

        TEST_METHOD(RaySphereIntersectionMiss)
        {
            Ray ray(Vec3D(0, 2, -5), Vec3D(0, 0, 1));
            Sphere sphere;

            CollisionInfo info = Collision::Intersect(ray, sphere);

            Assert::AreEqual(0, int(info.hits.size()));
        }

        TEST_METHOD(RaySphereIntersectionInside)
        {
            Ray ray(Vec3D(0, 0, 0), Vec3D(0, 0, 1));
            Sphere sphere;

            CollisionInfo info = Collision::Intersect(ray, sphere);

            Assert::AreEqual(2, int(info.hits.size()));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(-1.f, info.hits[0].distance));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(1.f, info.hits[1].distance));
        }

        TEST_METHOD(RaySphereIntersectionBehind)
        {
            Ray ray(Vec3D(0, 0, 5), Vec3D(0, 0, 1));
            Sphere sphere;

            CollisionInfo info = Collision::Intersect(ray, sphere);

            Assert::AreEqual(2, int(info.hits.size()));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(-6.f, info.hits[0].distance));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(-4.f, info.hits[1].distance));
        }

        TEST_METHOD(GetFirstHitTest)
        {
            Ray ray(Vec3D(0, 0, -5), Vec3D(0, 0, 1));
            Sphere sphere;

            CollisionInfo info = Collision::Intersect(ray, sphere);

            Assert::AreEqual(2, int(info.hits.size()));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(4.f, info.hits[0].distance));
            Assert::IsNotNull(info.GetFirstHit());
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(4.f, info.GetFirstHit()->distance));
        }

        TEST_METHOD(RayScaledSphereIntersection)
        {
            Ray ray(Vec3D(0, 0, -5), Vec3D(0, 0, 1));
            Sphere sphere;

            sphere.SetTransform(Transform::Scaling(2, 2, 2));

            CollisionInfo info = Collision::Intersect(ray, sphere);

            Assert::AreEqual(2, int(info.hits.size()));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(3.f, info.hits[0].distance));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(7.f, info.hits[1].distance));
        }
    };
}
