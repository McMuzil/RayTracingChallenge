#include "pch.h"
#include "CppUnitTest.h"
#include "RayTracer/Core/PointLight.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(PointLightTest)
    {
    public:

        TEST_METHOD(Constructor)
        {
            const Vec3D color(1, 1, 1);
            const Vec3D position(0.f);
            const PointLight pointLight(position, color);

            Assert::IsTrue(position.IsEqualWithEpsilon(pointLight.GetPosition()));
            Assert::IsTrue(color.IsEqualWithEpsilon(pointLight.GetColor()));
        }
    };
}
