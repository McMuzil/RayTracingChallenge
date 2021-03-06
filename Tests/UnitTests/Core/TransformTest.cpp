#include "pch.h"
#include "CppUnitTest.h"

#include "RayTracer/Core/Helpers.h"
#include "RayTracer/Core/Vector.h"
#include "RayTracer/Core/Canvas.h"
#include "RayTracer/Core/Transform.h"
#include "RayTracer/Core/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(TranslationTest)
    {
    public:

        TEST_METHOD(TranslatePoint)
        {
            const Matrix<4, 4> transform = Transform::Translation(5.f, -3.f, 2.f);
            Vec4D point(-3, 4, 5, 1);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(2, 1, 7, 1), transform * point));
        }

        TEST_METHOD(TranslatePointInversed)
        {
            const Matrix<4, 4> transform = Transform::Translation(5.f, -3.f, 2.f).Inverse();
            Vec4D point(-3, 4, 5, 1);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(-8, 7, 3, 1), transform * point));
        }

        TEST_METHOD(TranslateVector)
        {
            const Matrix<4, 4> transform = Transform::Translation(5.f, -3.f, 2.f);
            Vec4D vector(-3, 4, 5, 0);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(vector, transform * vector));
        }

        TEST_METHOD(ScalePoint)
        {
            const Matrix<4, 4> transform = Transform::Scaling(2, 3, 4);
            Vec4D point(-4, 6, 8, 1);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(-8, 18, 32, 1), transform * point));
        }

        TEST_METHOD(ScaleVector)
        {
            const Matrix<4, 4> transform = Transform::Scaling(2, 3, 4);
            Vec4D vector(-4, 6, 8, 0);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(-8, 18, 32), transform * vector));
        }

        TEST_METHOD(ScaleVectorInverse)
        {
            const Matrix<4, 4> transform = Transform::Scaling(2, 3, 4).Inverse();
            Vec4D vector(-4, 6, 8, 0);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(-2, 2, 2), transform * vector));
        }

        TEST_METHOD(ReflectVector)
        {
            const Matrix<4, 4> transform = Transform::Scaling(-1, 1, 1);
            Vec4D vector(-4, 6, 8);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(4, 6, 8), transform * vector));
        }

        TEST_METHOD(RotatePointAroundXAxis)
        {
            const Vec4D point(0, 1, 0, 1);

            const Matrix<4, 4> halfQuarter = Transform::RotationX(Constants::Pi / 4.f);
            const Matrix<4, 4> fullQuarter = Transform::RotationX(Constants::Pi / 2.f);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(0, sqrtf(2.f) / 2.f, sqrtf(2.f) / 2.f, 1), halfQuarter * point));
            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(0, 0, 1, 1), fullQuarter * point));
        }

        TEST_METHOD(RotatePointAroundXAxisInverse)
        {
            const Vec4D point(0, 1, 0, 1);

            const Matrix<4, 4> halfQuarter = Transform::RotationX(Constants::Pi / 4.f).Inverse();
            const Matrix<4, 4> fullQuarter = Transform::RotationX(Constants::Pi / 2.f).Inverse();

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(0, sqrtf(2.f) / 2.f, -(sqrtf(2.f) / 2.f), 1), halfQuarter * point));
            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(0, 0, -1, 1), fullQuarter * point));
        }

        TEST_METHOD(RotatePointAroundYAxis)
        {
            const Vec4D point(0, 0, 1, 1);

            const Matrix<4, 4> halfQuarter = Transform::RotationY(Constants::Pi / 4.f);
            const Matrix<4, 4> fullQuarter = Transform::RotationY(Constants::Pi / 2.f);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(sqrtf(2.f) / 2.f, 0.f, sqrtf(2.f) / 2.f, 1), halfQuarter * point));
            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(1, 0, 0, 1), fullQuarter * point));
        }

        TEST_METHOD(RotatePointAroundZAxis)
        {
            const Vec4D point(1, 0, 0, 1);

            const Matrix<4, 4> halfQuarter = Transform::RotationZ(Constants::Pi / 4.f);
            const Matrix<4, 4> fullQuarter = Transform::RotationZ(Constants::Pi / 2.f);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(sqrtf(2.f) / 2.f, sqrtf(2.f) / 2.f, 0.f, 1), halfQuarter * point));
            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(0, 1, 0, 1), fullQuarter * point));
        }

        TEST_METHOD(ShearXToY)
        {
            const Matrix<4, 4> transform = Transform::Shearing(1, 0, 0, 0, 0, 0);
            const Vec4D point(2, 3, 4);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(5, 3, 4), transform * point));
        }

        TEST_METHOD(ShearXToZ)
        {
            const Matrix<4, 4> transform = Transform::Shearing(0, 1, 0, 0, 0, 0);
            const Vec4D point(2, 3, 4);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(6, 3, 4), transform * point));
        }

        TEST_METHOD(ShearYToX)
        {
            const Matrix<4, 4> transform = Transform::Shearing(0, 0, 1, 0, 0, 0);
            const Vec4D point(2, 3, 4);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(2, 5, 4), transform * point));
        }

        TEST_METHOD(ShearYToZ)
        {
            const Matrix<4, 4> transform = Transform::Shearing(0, 0, 0, 1, 0, 0);
            const Vec4D point(2, 3, 4);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(2, 7, 4), transform * point));
        }

        TEST_METHOD(ShearZToX)
        {
            const Matrix<4, 4> transform = Transform::Shearing(0, 0, 0, 0, 1, 0);
            const Vec4D point(2, 3, 4);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(2, 3, 6), transform * point));
        }

        TEST_METHOD(ShearZToY)
        {
            const Matrix<4, 4> transform = Transform::Shearing(0, 0, 0, 0, 0, 1);
            const Vec4D point(2, 3, 4);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(2, 3, 7), transform * point));
        }

        TEST_METHOD(TransfomationSequenced)
        {
            Vec4D point(1, 0, 1, 1);
            const Matrix<4, 4> rotationX = Transform::RotationX(Constants::Pi / 2.f);
            const Matrix<4, 4> scaling = Transform::Scaling(5, 5, 5);
            const Matrix<4, 4> translation = Transform::Translation(10, 5, 7);

            point = rotationX * point;
            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(1, -1, 0, 1), point));

            point = scaling * point;
            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(5, -5, 0, 1), point));

            point = translation * point;
            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(15, 0, 7, 1), point));
        }

        TEST_METHOD(TransfomationChained)
        {
            Vec4D point(1, 0, 1, 1);
            const Matrix<4, 4> rotationX = Transform::RotationX(Constants::Pi / 2.f);
            const Matrix<4, 4> scaling = Transform::Scaling(5, 5, 5);
            const Matrix<4, 4> translation = Transform::Translation(10, 5, 7);

            const Matrix<4, 4> transform = translation * scaling * rotationX;
            point = transform * point;

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(Vec4D(15, 0, 7, 1), point));
        }

        TEST_METHOD(LookAtDefault)
        {
            Vec3D point(0, 0, 0);
            Vec3D target(0, 0, -1);
            Vec3D up(0, 1, 0);

            Matrix<4, 4> transform = Transform::LookAt(point, target, up);

            Assert::IsTrue(transform.IsEqualWithEpsilon(Matrix<4, 4>::Identity()), L"Must be an identity matrix.");
        }

        TEST_METHOD(LookAtPositiveZ)
        {
            Vec3D point(0, 0, 0);
            Vec3D target(0, 0, 1);
            Vec3D up(0, 1, 0);

            Matrix<4, 4> transform = Transform::LookAt(point, target, up);

            Assert::IsTrue(transform.IsEqualWithEpsilon(Transform::Scaling(-1, 1, -1)), L"Matrices are not equal.");
        }

        TEST_METHOD(LookAtMovesWorld)
        {
            Vec3D point(0, 0, 8);
            Vec3D target(0, 0, 0);
            Vec3D up(0, 1, 0);

            Matrix<4, 4> transform = Transform::LookAt(point, target, up);

            Assert::IsTrue(transform.IsEqualWithEpsilon(Transform::Translation(0, 0, -8)), L"Matrices are not equal.");
        }

        TEST_METHOD(LookAtArbitraryDirection)
        {
            Vec3D point(1, 3, 2);
            Vec3D target(4, -2, 8);
            Vec3D up(1, 1, 0);

            Matrix<4, 4> transform = Transform::LookAt(point, target, up);

            Matrix<4, 4> expected{
                { -0.50709f, 0.50709f,  0.67612f, -2.36643f },
                {  0.76772f, 0.60609f,  0.12122f, -2.82843f },
                { -0.35857f, 0.59761f, -0.71714f,  0.00000f },
                {  0.00000f, 0.00000f,  0.00000f,  1.00000f },
            };

            Assert::IsTrue(expected.IsEqualWithEpsilon(transform), L"Matrices are not equal.");
        }
    };
}
