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
    };
}
