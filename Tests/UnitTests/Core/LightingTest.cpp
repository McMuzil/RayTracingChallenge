#include "pch.h"
#include "CppUnitTest.h"
#include "Core/Material.h"
#include "Core/Vector.h"
#include "Core/PointLight.h"
#include "Core/Lighting.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(LightingTest)
    {
    public:

        const Material DefaultMaterial;
        const Vec3D Position;

        TEST_METHOD(EyeBetweenLightAndSurface)
        {
            Vec3D toEye(0, 0, -1);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 0, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultMaterial, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(1.9f, 1.9f, 1.9f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(EyeBetweenLightAndSurfaceAndEyeOffset45)
        {
            float f = sqrt(2.f) / 2.f;
            Vec3D toEye(0, f, -f);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 0, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultMaterial, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(1.f, 1.f, 1.f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(EyeOppositeSurfaceAndLightOffset45)
        {
            Vec3D toEye(0, 0, -1);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 10, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultMaterial, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(0.7364f, 0.7364f, 0.7364f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(EyeInPathOfReflectionVector)
        {
            float f = sqrt(2.f) / 2.f;
            Vec3D toEye(0, -f, -f);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 10, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultMaterial, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(1.63638f, 1.63638f, 1.63638f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(LightBehindSurface)
        {
            Vec3D toEye(0, 0, -1);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 0, 10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultMaterial, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(0.1f, 0.1f, 0.1f).IsEqualWithEpsilon(result));
        }
    };
}
