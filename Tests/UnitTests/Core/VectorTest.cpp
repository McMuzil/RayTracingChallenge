#include "pch.h"
#include "CppUnitTest.h"

#include <Core/Vector.h>
#include <Core/Helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(VectorUnitTest)
	{
	public:
		
		TEST_METHOD(VectorCreatedByDefault)
		{
            Vec2D vec2D;
            Vec3D vec3D;
            Vec4D vec4D;

            
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(vec2D.y, 0.f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(vec3D.z, 0.f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(vec4D.w, 0.f));
		}

        TEST_METHOD(XYZWEqualToRGBA)
        {
            Vec4D vec4D;

            Assert::AreEqual(vec4D.x, vec4D.r);
            Assert::AreEqual(vec4D.y, vec4D.g);
            Assert::AreEqual(vec4D.z, vec4D.b);
            Assert::AreEqual(vec4D.w, vec4D.a);
        }

        TEST_METHOD(PropertyWorks)
        {
            Vec4D vec4D;
            Vec4D vec4DProperty;

            vec4D.SetX(1.f);
            vec4DProperty.x = 1.f;

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(vec4D.GetX(), vec4DProperty.x));

            vec4D.SetY(1.f);
            vec4DProperty.y = 1.f;

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(vec4D.GetY(), vec4DProperty.y));

            vec4D.SetZ(1.f);
            vec4DProperty.z = 1.f;

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(vec4D.GetZ(), vec4DProperty.z));

            vec4D.SetW(1.f);
            vec4DProperty.w = 1.f;

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(vec4D.GetW(), vec4DProperty.w));
        }

        TEST_METHOD(EqualOperatorWorks)
        {
            Vec4D first(10.f);
            Vec4D second(10.f);


            Assert::IsTrue(first == second);
        }

        TEST_METHOD(LessOperatorWorks)
        {
            Vec4D first(10.f);
            Vec4D second(11.f);

            Assert::IsTrue(first < second);
        }

        TEST_METHOD(GreaterOperatorWorks)
        {
            Vec4D first(11.f);
            Vec4D second(10.f);

            Assert::IsTrue(first > second);
        }

        TEST_METHOD(IsVectorEqualWithEpsilonTest)
        {
            Vec4D first(10.000001f);
            Vec4D second(10.000002f);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(first, second, 1e-5f));
        }

        TEST_METHOD(AddOperatorTest)
        {
            const Vec4D first(1.f);
            const Vec4D second(1.f);

            const Vec4D result = first + second;
            const Vec4D expectedResult(2.f, 2.f, 2.f, 2.f);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(result, expectedResult));
        }

        TEST_METHOD(SubstractOperatorTest)
        {
            const Vec4D first(1.f);
            const Vec4D second(1.f);

            const Vec4D result = first - second;
            const Vec4D expectedResult(0.f);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(result, expectedResult));
        }

        TEST_METHOD(MultiplyOperatorTest)
        {
            const Vec4D first(3.f);
            const Vec4D second(5.f);

            const Vec4D result = first * second;
            const Vec4D expectedResult(15.f);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(result, expectedResult));
        }

        TEST_METHOD(UnaryMinusOperatorTest)
        {
            const Vec4D first(1.f);

            const Vec4D result = -first;
            const Vec4D expectedResult(-1.f);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(result, expectedResult));
        }

        TEST_METHOD(ScalarMultiplication)
        {
            const Vec4D first(1.f, 2.f, 3.f, 4.f);

            const Vec4D result = first * 5.f;
            const Vec4D expectedResult(5.f, 10.f, 15.f, 20.f);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(result, expectedResult));
        }

        TEST_METHOD(ScalarDivision)
        {
            const Vec4D first(1.f, 2.f, 3.f, 4.f);

            const Vec4D result = first / 2.f;
            const Vec4D expectedResult(0.5f, 1.f, 1.5f, 2.f);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(result, expectedResult));
        }

        TEST_METHOD(MagnitudeSingleComponent)
        {
            const Vec4D first(1.f, 0.f, 0.f, 0.f);

            const float result = first.Length();
            const float expectedResult = 1.f;

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(result, expectedResult));
        }

        TEST_METHOD(MagnitudeAllComponents)
        {
            const Vec4D first(1.f, 2.f, 3.f, 0.f);

            const float result = first.Length();
            const float expectedResult = sqrt(1.f*1.f + 2.f*2.f + 3.f*3.f);

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(result, expectedResult));
        }

        TEST_METHOD(NormalizeTest)
        {
            const Vec4D vec(4.f, 0.f);
            
            const Vec4D normalizedVec = vec.Normalize();
            const Vec4D expectedResult = Vec4D(1.f, 0.f);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(normalizedVec, expectedResult));
        }

        TEST_METHOD(DotProductTest)
        {
            const Vec4D first(1.f, 2.f, 3.f);
            const Vec4D second(2.f, 3.f, 4.f);

            const float result = first.Dot(second);
            const float expectedResult = 20.f;

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(result, expectedResult));
        }

        TEST_METHOD(CrossProductTest)
        {
            const Vec4D first(1.f, 2.f, 3.f);
            const Vec4D second(2.f, 3.f, 4.f);

            const Vec4D firstCrossSecond = first.Cross(second);
            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(firstCrossSecond, Vec4D(-1.f, 2.f, -1.f)));

            const Vec4D secondCrossfirst = second.Cross(first);
            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(secondCrossfirst, Vec4D(1.f, -2.f, 1.f)));
        }
	};
}
