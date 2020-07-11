#include "pch.h"
#include "CppUnitTest.h"

#include "Core/Sphere.h"
#include "Core/Transform.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(SphereTest)
    {
    public:

        TEST_METHOD(DefaultTransformation)
        {
            Sphere sphere;

            Assert::IsTrue(Matrix<4, 4>::Identity().IsEqualWithEpsilon(sphere.GetTransform()));
        }

        TEST_METHOD(SetTranform)
        {
            Sphere sphere;

            Matrix<4, 4> t = Transform::Translation(2, 3, 4);
            sphere.SetTransform(t);

            Assert::IsTrue(t.IsEqualWithEpsilon(sphere.GetTransform()));
        }

        TEST_METHOD(NormalAtAxisX)
        {
            const Sphere s;
            const Vec3D normal = s.NormalAt(1, 0, 0);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(1, 0, 0), normal));
        }

        TEST_METHOD(NormalAtAxisY)
        {
            const Sphere s;
            const Vec3D normal = s.NormalAt(0, 1, 0);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(0, 1, 0), normal));
        }

        TEST_METHOD(NormalAtAxisZ)
        {
            const Sphere s;
            const Vec3D normal = s.NormalAt(0, 0, 1);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(0, 0, 1), normal));
        }

        TEST_METHOD(NormalAtNonaxialPoint)
        {
            const Sphere s;
            const float f = sqrt(3.f) / 3.f;
            const Vec3D normal = s.NormalAt(f, f, f);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(f, f, f), normal));
        }

        TEST_METHOD(NormalIsNormalized)
        {
            const Sphere s;
            const float f = sqrt(3.f) / 3.f;
            const Vec3D normal = s.NormalAt(f, f, f);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(normal, normal.Normalize()));
        }

        TEST_METHOD(NormalOnTranslatedSphere)
        {
            Sphere s;
            s.SetTransform(Transform::Translation(0, 1, 0));
            const Vec3D normal = s.NormalAt(0, 1.70711f, -0.70711f);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(0, 0.70711f, -0.70711f), normal));
        }

        TEST_METHOD(NormalOnTransformedSphere)
        {
            Sphere s;
            Matrix<4, 4> transform = Transform::Scaling(1.f, 0.5f, 1.f) * Transform::RotationZ(Constants::Pi / 5.f);
            s.SetTransform(transform);
            const float f = sqrt(2.f) / 2.f;
            const Vec3D normal = s.NormalAt(0, f, -f);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(0, 0.97014f, -0.24254f), normal));
        }
    };
}
