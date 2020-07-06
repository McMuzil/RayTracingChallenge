#include "pch.h"
#include "CppUnitTest.h"

#include "Core/Helpers.h"
#include "Core/Matrix.h"
#include "Core/Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(MatrixTest)
    {
    public:

        TEST_METHOD(Constructor2x2)
        {
            const Matrix<2, 2> matrix(
                { 1, 2 },
                { 1, 2 }
            );

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[0][0], 1));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[0][1], 2));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[1][0], 1));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[1][1], 2));
        }

        TEST_METHOD(Constructor2x4)
        {
            const Matrix<2, 4> matrix(
                { 1, 2, 3, 4 },
                { 1, 2, 3, 4 }
            );

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[0][0], 1));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[0][3], 4));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[1][0], 1));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[1][3], 4));
        }

        TEST_METHOD(Constructor4x2)
        {
            const Matrix<4, 2> matrix(
                { 1, 2 },
                { 1, 2 },
                { 1, 2 },
                { 1, 2 }
            );

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[0][0], 1));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[0][1], 2));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[1][0], 1));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[1][1], 2));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[2][0], 1));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[2][1], 2));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[3][0], 1));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[3][1], 2));
        }

        TEST_METHOD(Constructor3x4)
        {
            const Matrix<3, 4> matrix(
                { 1,    2,    3,   4   },
                { 5.5f, 6.5f, 7.5, 8.5 },
                { 9,    10,   11,  12  }
            );

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[0][0], 1));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[0][3], 4));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[1][0], 5.5f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[1][2], 7.5f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[2][2], 11));
        }

        TEST_METHOD(Constructor4x4)
        {
            const Matrix<4, 4> matrix(
                { 1,     2,     3,     4     },
                { 5.5f,  6.5f,  7.5,   8.5   },
                { 9,     10,    11,    12    },
                { 13.5f, 14.5f, 15.5f, 16.5f }
            );

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[0][0], 1));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[0][3], 4));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[1][0], 5.5f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[1][2], 7.5f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[2][2], 11));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[3][0], 13.5f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[3][2], 15.5f));
        }

        TEST_METHOD(Fill)
        {
            const Matrix<4, 4> matrix(1.f);

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[0][0], 1.f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(matrix[3][3], 1.f));
        }

        TEST_METHOD(AddOperator)
        {
            const Matrix<4, 4> matrixA(1.f);
            const Matrix<4, 4> matrixB(1.f);

            const Matrix<4, 4> result = matrixA + matrixB;
            const Matrix<4, 4> expectedResult(2.f);

            Assert::IsTrue(result.IsEqualWithEpsilon(expectedResult));
        }

        TEST_METHOD(SubtractOperator)
        {
            const Matrix<4, 4> matrixA(2.f);
            const Matrix<4, 4> matrixB(1.f);

            const Matrix<4, 4> result = matrixA - matrixB;
            const Matrix<4, 4> expectedResult(1.f);

            Assert::IsTrue(result.IsEqualWithEpsilon(expectedResult));
        }

        TEST_METHOD(MultiplyOperatorMatrixVSMatrixSameSize)
        {
            const Matrix<4, 4> matrixA(
                { 1, 2, 3, 4 },
                { 5, 6, 7, 8 },
                { 9, 8, 7, 6 },
                { 5, 4, 3, 2 }
            );

            const Matrix<4, 4> matrixB(
                { -2, 1, 2,  3 },
                {  3, 2, 1, -1 },
                {  4, 3, 6,  5 },
                {  1, 2, 7,  8 }
            );

            const Matrix<4, 4> result = matrixA * matrixB;
            const Matrix<4, 4> expectedResult(
                { 20, 22, 50,  48 },
                { 44, 54, 114, 108 },
                { 40, 58, 110, 102 },
                { 16, 26, 46,  42 }
            );

            Assert::IsTrue(result.IsEqualWithEpsilon(expectedResult));
        }

        TEST_METHOD(MultiplyOperatorDifferentSize)
        {
            const Matrix<2, 4> matrixA(
                { 3, 2, 1, 5 },
                { 9, 1, 3, 0 }
            );

            const Matrix<4, 3> matrixB(
                { 2, 9, 0 },
                { 1, 3, 5 },
                { 2, 4, 7 },
                { 8, 1, 5 }
            );

            const Matrix<2, 3> result = matrixA * matrixB;

            const Matrix<2, 3> expectedResult(
                { 50, 42, 42 },
                { 25, 96, 26 }
            );

            Assert::IsTrue(result.IsEqualWithEpsilon(expectedResult));
        }

        TEST_METHOD(MultiplyOperatorMatrixVSVector)
        {
            const Matrix<4, 4> matrixA(
                { 1, 2, 3, 4 },
                { 2, 4, 4, 2 },
                { 8, 6, 4, 1 },
                { 0, 0, 0, 1 }
            );

            const Vec4D vector(1, 2, 3, 1);

            const Vec4D expectedResult(18, 24, 33, 1);
            const Vec4D result = matrixA * vector;
        }

        TEST_METHOD(MultiplyOperatorIdentityMatrix)
        {
            const Matrix<4, 4> matrixA(
                { 1,     2,     3,     4     },
                { 5.5f,  6.5f,  7.5,   8.5   },
                { 9,     10,    11,    12    },
                { 13.5f, 14.5f, 15.5f, 16.5f }
            );

            const Matrix<4, 4> result = matrixA * Matrix<4, 4>::Identity();

            Assert::IsTrue(result.IsEqualWithEpsilon(matrixA));
        }

        TEST_METHOD(Comparison)
        {
            const Matrix<4, 4> matrixA(
                { 1,     2,     3,     4     },
                { 5.5f,  6.5f,  7.5,   8.5   },
                { 9,     10,    11,    12    },
                { 13.5f, 14.5f, 15.5f, 16.5f }
            );

            const Matrix<4, 4> matrixB(
                { 1,     2,     3,     4     },
                { 5.5f,  6.5f,  7.5,   8.5   },
                { 9,     10,    11,    12    },
                { 13.5f, 14.5f, 15.5f, 16.5f }
            );

            Assert::IsTrue(matrixA.IsEqualWithEpsilon(matrixB));
            Assert::IsTrue(Matrix<4, 4>::IsEqualWithEpsilon(matrixA, matrixB));
        }

        TEST_METHOD(Transpose4x4)
        {
            const Matrix<4, 4> matrix(
                { 1,     2,     3,     4     },
                { 5.5f,  6.5f,  7.5,   8.5   },
                { 9,     10,    11,    12    },
                { 13.5f, 14.5f, 15.5f, 16.5f }
            );

            const Matrix<4, 4> result = matrix.Transpose();
            const Matrix<4, 4> expectedResult(
                { 1,   5.5,  9,    13.5f },
                { 2.f, 6.5f, 10.f, 14.5f },
                { 3.f, 7.5f,  11,  15.5f },
                { 4.f, 8.5f, 12.f, 16.5f }
            );

            Assert::IsTrue(result.IsEqualWithEpsilon(expectedResult));
        }

        TEST_METHOD(Transpose2x4)
        {
            const Matrix<2, 4> matrix(
                { 1,    2,    3, 4 },
                { 5.5f, 6.5f, 7, 8 }
            );

            const Matrix<4, 2> expectedResult(
                { 1,   5.5, },
                { 2.f, 6.5f },
                { 3.f, 7.f },
                { 4.f, 8.f }
            );

            const Matrix<4, 2> result = matrix.Transpose();

            Assert::IsTrue(result.IsEqualWithEpsilon(expectedResult));
        }

        TEST_METHOD(TransposeIdentity)
        {
            const Matrix<4, 4> matrix = Matrix<4, 4>::Identity();

            const Matrix<4, 4> result = matrix.Transpose();
            const Matrix<4, 4> expectedResult = Matrix<4, 4>::Identity();

            Assert::IsTrue(result.IsEqualWithEpsilon(expectedResult));
        }

        TEST_METHOD(Determinant2x2)
        {
            const float a = 1.f;
            const float b = 5.f;
            const float c = -5.f;
            const float d = 3.f;

            const Matrix<2, 2> matrix(
                { a, b },
                { c, d }
            );

            const float expectedResult = (a * d) - (b * c);
            const float result = matrix.Determinant();

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(result, expectedResult));
        }

        TEST_METHOD(Determinant3x3)
        {
            const Matrix<3, 3> matrix(
                { 1,  2,  6 },
                { -5,  8, -4 },
                { 2,  6,  4 }
            );

            const float cofactor1 = matrix.Cofactor(0, 0);
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(56, cofactor1));

            const float cofactor2 = matrix.Cofactor(0, 1);
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(12, cofactor2));

            const float cofactor3 = matrix.Cofactor(0, 2);
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(-46, cofactor3));

            const float determinant = matrix.Determinant();
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(determinant, -196));
        }

        TEST_METHOD(Determinant4x4)
        {
            const Matrix<4, 4> matrix(
                { -2, -8,  3,  5 },
                { -3,  1,  7,  3 },
                { 1,  2, -9,  6  },
                { -6,  7,  7, -9 }
            );

            const float cofactor1 = matrix.Cofactor(0, 0);
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(690, cofactor1));

            const float cofactor2 = matrix.Cofactor(0, 1);
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(447, cofactor2));

            const float cofactor3 = matrix.Cofactor(0, 2);
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(210, cofactor3));

            const float cofactor4 = matrix.Cofactor(0, 3);
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(51, cofactor4));

            const float determinant = matrix.Determinant();
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(determinant, -4071));
        }

        TEST_METHOD(Submatrix3x3)
        {
            const Matrix<4, 4> matrix(
                { 1,     2,     3,     4     },
                { 5.5f,  6.5f,  7.5,   8.5   },
                { 9,     10,    11,    12    },
                { 13.5f, 14.5f, 15.5f, 16.5f }
            );
            const Matrix<3, 3> result = matrix.Submatrix(3, 3);
            const Matrix<3, 3> expectedResult(
                { 1,     2,     3   },
                { 5.5f,  6.5f,  7.5 },
                { 9,     10,    11  }
            );

            Assert::IsTrue(result.IsEqualWithEpsilon(expectedResult));
        }

        TEST_METHOD(Minor3x3)
        {
            const Matrix<3, 3, int32_t> matrix(
                { 3,  5,  0 },
                { 2, -1, -7 },
                { 6, -1,  5 }
            );

            const int32_t result = matrix.Minor(1, 0);
            const int32_t expectedResult = 25;

            Assert::AreEqual(expectedResult, result);
        }

        TEST_METHOD(Cofactor3x3)
        {
            const Matrix<3, 3, int32_t> matrix(
                { 3,  5,  0 },
                { 2, -1, -7 },
                { 6, -1,  5 }
            );

            Assert::AreEqual(-12, matrix.Minor(0, 0));
            Assert::AreEqual(-12, matrix.Cofactor(0, 0));
            Assert::AreEqual(25, matrix.Minor(1, 0));
            Assert::AreEqual(-25, matrix.Cofactor(1, 0));
        }

        TEST_METHOD(IsInvertibleTrue)
        {
            const Matrix<4, 4> matrix(
                { 6,  4, 4,  4 },
                { 5,  5, 7,  6 },
                { 4, -9, 3, -7 },
                { 9,  1, 7, -6 }
            );

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(-2120, matrix.Determinant()));
            Assert::AreEqual(true, matrix.IsInvertible());
        }

        TEST_METHOD(IsInvertibleFalse)
        {
            const Matrix<4, 4> matrix(
                { -4,  2, -2, -3 },
                {  9,  6,  2,  6 },
                {  0, -5,  1, -5 },
                {  0,  0,  0,  0 }
            );

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(0, matrix.Determinant()));
            Assert::AreEqual(false, matrix.IsInvertible());
        }

        TEST_METHOD(Inverse4x4)
        {
            const Matrix<4, 4> matrix(
                { -5,  2,  6, -8 },
                {  1, -5,  1,  8 },
                {  7,  7, -6, -7 },
                {  1, -3,  7,  4 }
            );

            const Matrix<4, 4> inversed = matrix.Inverse();

            Assert::IsTrue(Helpers::IsEqualWithEpsilon(532, matrix.Determinant()));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(-160, matrix.Cofactor(2, 3)));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(inversed[3][2], -160.f/532.f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(105, matrix.Cofactor(3, 2)));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(inversed[2][3], 105.f / 532.f));
            
            const Matrix<4, 4> expectedResult = Matrix<4, 4>(
                {  0.21805f,  0.45113f,   0.24060f, -0.04511f },
                { -0.80827f, -1.45677f, -0.44361f,  0.52068f },
                { -0.07895f, -0.22368f, -0.05263f,  0.19737f },
                { -0.52256f, -0.81391f, -0.30075f,  0.30639f }
            );

            Assert::IsTrue(expectedResult.IsEqualWithEpsilon(inversed));

            const Matrix<4, 4> matrix2(
                {  8, -5,  9,  2 },
                {  7,  5,  6,  1 },
                { -6,  0,  9,  6 },
                { -3,  0, -9, -4 }
            );

            const Matrix<4, 4> expectedResult2(
                { -0.15385f, -0.15385f, -0.28205f, -0.53846f },
                { -0.07692f,  0.12308f,  0.02564f,  0.03077f },
                {  0.35897f,  0.35897f,  0.43590f,  0.92308f },
                { -0.69231f, -0.69231f, -0.76923f, -1.92308f }
            );

            Assert::IsTrue(expectedResult2.IsEqualWithEpsilon(matrix2.Inverse()));
        }

        TEST_METHOD(InverseMultiply4x4)
        {
            const Matrix<4, 4> a(
                { 3, -9,  7,  3 },
                { 3,  -8,  2,  -9 },
                { -4,  4,  4,  1 },
                { -6,  5, -1, 1 }
            );

            const Matrix<4, 4> b(
                {  8, 2, 2, 2 },
                {  1, 2, 3, 4 },
                {  5, 4, 3, 1 },
                { -5, 2, 1, 5 }
            );

            const Matrix<4, 4> c = a * b;

            Assert::IsTrue(a.IsEqualWithEpsilon(c * b.Inverse()));
        }

        TEST_METHOD(SetRow)
        {
            Matrix<4, 4> matrix = Matrix<4, 4>::Identity();
            const Vec3D row(1, 2, 3);

            matrix.SetRow(3, row);
            const Matrix<4, 4> expectedResult(
                { 1, 0, 0, 0 },
                { 0, 1, 0, 0 },
                { 0, 0, 1, 0 },
                { 1, 2, 3, 1 }
            );

            Assert::IsTrue(expectedResult.IsEqualWithEpsilon(matrix));
        }

        TEST_METHOD(SetColumn)
        {
            Matrix<4, 4> matrix = Matrix<4, 4>::Identity();
            const Vec3D column(1, 2, 3);

            matrix.SetColumn(3, column);
            const Matrix<4, 4> expectedResult(
                { 1, 0, 0, 1 },
                { 0, 1, 0, 2 },
                { 0, 0, 1, 3 },
                { 0, 0, 0, 1 }
            );

            Assert::IsTrue(expectedResult.IsEqualWithEpsilon(matrix));
        }
    };
}
