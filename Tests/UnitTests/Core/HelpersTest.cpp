#include "pch.h"
#include "CppUnitTest.h"

#include "RayTracer/Core/Helpers.h"
#include "RayTracer/Core/Vector.h"
#include "RayTracer/Core/Objects/Object.h"
#include "RayTracer/Core/Matrix.h"
#include "RayTracer/Core/ObjectHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(HelpersTest)
    {
    public:

        TEST_METHOD(FloatEpsilonCheckFiveDigit)
        {
            float first =  1.000001f;
            float second = 1.000002f;

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(first, second, 1e-5f));
        }

        TEST_METHOD(FloatEpsilonCheckTenDigit)
        {
            float first =  1.00000000001f;
            float second = 1.00000000002f;

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(first, second, 1e-10f));
        }

        TEST_METHOD(CreateGlassSphere)
        {
            std::unique_ptr<Object> sphere = Helpers::CreateGlassSphere();

            Assert::IsTrue(sphere->GetTransform().IsEqualWithEpsilon(Matrix<4, 4>::Identity()));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(sphere->GetMaterial().GetTransparency(), 1.f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(sphere->GetMaterial().GetRefractiveIndex(), 1.5f));
        }
    };
}
