#include "pch.h"
#include "CppUnitTest.h"

#include "RayTracer/Core/Helpers.h"
#include "RayTracer/Core/Vector.h"
#include "RayTracer/Core/Ray.h"
#include "RayTracer/Core/Transform.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(RayTest)
    {
    public:

        TEST_METHOD(CreateRay)
        {
            Vec3D origin(1, 2, 3);
            Vec3D direction(4, 5, 6);

            Ray ray(origin, direction);

            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(origin, ray.GetOrigin()));
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(direction, ray.GetDirection()));
        }

        TEST_METHOD(GetPointAtDistance)
        {
            Ray ray(Vec3D(2, 3, 4), Vec3D(1, 0, 0));

            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(2, 3, 4), ray.GetPointAtDistance(0)));
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(3, 3, 4), ray.GetPointAtDistance(1)));
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(1, 3, 4), ray.GetPointAtDistance(-1)));
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(4.5f, 3, 4), ray.GetPointAtDistance(2.5)));
        }

        TEST_METHOD(Translate)
        {
            const Ray ray(Vec3D(1, 2, 3), Vec3D(0, 1, 0));

            const Matrix<4, 4> translation = Transform::Translation(3, 4, 5);
            const Ray resultRay = ray.Transform(translation);

            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(4, 6, 8), resultRay.GetOrigin()));
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(0, 1, 0), resultRay.GetDirection()));
        }

        TEST_METHOD(Scale)
        {
            const Ray ray(Vec3D(1, 2, 3), Vec3D(0, 1, 0));

            const Matrix<4, 4> scaling = Transform::Scaling(2, 3, 4);
            const Ray resultRay = ray.Transform(scaling);

            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(2, 6, 12), resultRay.GetOrigin()));
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(0, 3, 0), resultRay.GetDirection()));
        }
    };
}
