#include "pch.h"
#include "CppUnitTest.h"

#include <Core/Helpers.h>
#include <Core/Vector.h>

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
    };
}
