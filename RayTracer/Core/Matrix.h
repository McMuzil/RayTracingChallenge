#pragma once

#include <array>
#include <assert.h>
#include "Vector.h"
#include "vector"

template <size_t N, size_t M, typename T = float>
class Matrix
{
public:
    constexpr static size_t RowsNumber = N;
    constexpr static size_t ColumnsNumber = M;
    using Row = Vector<T, ColumnsNumber>;
    using MatrixArray = std::array<Row, RowsNumber>;

public:
    Matrix()
        : m_data(MatrixArray())
    {
    }

    explicit Matrix(T value)
    {
        Fill(value);
    }

    template<typename T = Row>
    Matrix(const Row& first,
           const typename std::enable_if_t<std::is_convertible<T, Row>::value && RowsNumber == 2, Row>& second = Row())
        : m_data{ first, second }
    {
    }

    template <typename T = Row>
    Matrix(const T& first, const T& second = Row(), const typename std::enable_if_t<std::is_convertible<T, Row>::value && RowsNumber == 3, Row>& third = Row())
        : m_data{ first, second, third }
    {
    }

    template <typename T = Row>
    Matrix(const T& first, const T& second = Row(), const T& third = Row(), const typename std::enable_if_t<std::is_convertible<T, Row>::value && RowsNumber == 4, Row>& fourth = Row())
        : m_data{ first, second, third, fourth }
    {
    }

    void Fill(T value)
    {
        m_data.fill(Row(value));
    }

    bool IsEqualWithEpsilon(const Matrix& other, T epsilon = Constants::Epsilon) const
    {
        for (size_t i = 0; i < RowsNumber; i++)
        {
            for (size_t j = 0; j < ColumnsNumber; j++)
            {
                if (abs(m_data[i][j] - other[i][j]) > epsilon)
                {
                    return false;
                }
            }
        }

        return true;
    }

    static bool IsEqualWithEpsilon(const Matrix& first, const Matrix& second, T epsilon = Constants::Epsilon)
    {
        for (size_t i = 0; i < RowsNumber; i++)
        {
            for (size_t j = 0; j < ColumnsNumber; j++)
            {
                if (abs(first[i][j] - second[i][j]) > epsilon)
                {
                    return false;
                }
            }
        }

        return true;
    }

    static const Matrix& Identity()
    {
        static_assert(ColumnsNumber == RowsNumber, "Trying to take identity matrix of not squared matrix.");
        static Matrix identity = MakeIdentityMatrix();
        return identity;
    }

    Matrix<ColumnsNumber, RowsNumber> Transpose() const
    {
        Matrix<ColumnsNumber, RowsNumber> matrix;

        for (size_t i = 0; i < RowsNumber; i++)
        {
            for (size_t j = 0; j < ColumnsNumber; j++)
            {
                matrix[j][i] = m_data[i][j];
            }
        }

        return matrix;
    }

    template<class M = Matrix>
    Matrix<M::RowsNumber - 1, M::ColumnsNumber - 1, T> Submatrix(size_t row, size_t column) const
    {
        static_assert(M::RowsNumber == M::ColumnsNumber, "Trying to get submatrix of not squared matrix.");
        static_assert(M::RowsNumber >= 2, "You can't get submatrix of the matrix with size fewer than 2.");
        assert(row < RowsNumber);

        Matrix<M::RowsNumber - 1, M::ColumnsNumber - 1, T> submatrix;

        bool hasSkippedRow = false;
        for (size_t i = 0; i < RowsNumber; i++)
        {
            if (i == row)
            {
                hasSkippedRow = true;
                continue;
            }

            bool hasSkippedColumn = false;
            for (size_t j = 0; j < ColumnsNumber; j++)
            {
                if (j == column)
                {
                    hasSkippedColumn = true;
                    continue;
                }

                submatrix[hasSkippedRow ? i - 1 : i][hasSkippedColumn ? j - 1 : j] = m_data[i][j];
            }
        }

        return submatrix;
    }

    T Cofactor(size_t row, size_t column) const
    {
        static_assert(std::is_signed<T>::value, "You're trying to take cofactor with an unsigned values.");
        return (row + column) % 2 == 1
            ? -Minor(row, column)
            :  Minor(row, column);
    }

    T Minor(size_t row, size_t column) const
    {
        auto matrix = Submatrix(row, column);
        return matrix.Determinant();
    }

    T Determinant() const
    {
        return Determinant(*this);
    }

    bool IsInvertible() const
    {
        return !Helpers::IsEqualWithEpsilon(0.f, Determinant());
    }

    Matrix Inverse() const
    {
        assert(IsInvertible());
        if (!IsInvertible())
        {
            return Matrix::Identity();
        }

        Matrix result;
        const T determinant = Determinant();

        for (size_t i = 0; i < RowsNumber; i++)
        {
            for (size_t j = 0; j < ColumnsNumber; j++)
            {
                result[j][i] = Cofactor(i, j) / determinant;
            }
        }

        return result;
    }

    template<typename Vec = Row>
    void SetRow(size_t rowNumber, const Vec& vec)
    {
        for (size_t i = 0; i < Vec::Size; i++)
        {
            m_data[rowNumber][i] = vec[i];
        }
    }

    template<typename Vec = Row>
    void SetColumn(size_t columnNumber, const Vec& vec)
    {
        for (size_t i = 0; i < Vec::Size; i++)
        {
            m_data[i][columnNumber] = vec[i];
        }
    }

    Vec2Du GetSize() const
    {
        return Vec2Du(ColumnsNumber, RowsNumber);
    }

    Matrix operator+(const Matrix& other) const
    {
        Matrix matrix;

        for (size_t i = 0; i < RowsNumber; i++)
        {
            for (size_t j = 0; j < ColumnsNumber; j++)
            {
                matrix[i][j] = m_data[i][j] + other.m_data[i][j];
            }
        }

        return matrix;
    }

    Matrix operator-(const Matrix& other) const
    {
        Matrix matrix;

        for (size_t i = 0; i < RowsNumber; i++)
        {
            for (size_t j = 0; j < ColumnsNumber; j++)
            {
                matrix[i][j] = m_data[i][j] - other.m_data[i][j];
            }
        }

        return matrix;
    }

    template<typename M = Matrix>
    Matrix<Matrix::RowsNumber, M::ColumnsNumber> operator*(const M& other) const
    {
        static_assert(ColumnsNumber == M::RowsNumber, "Trying");
        Matrix<RowsNumber, M::ColumnsNumber> matrix;

        for (size_t i = 0; i < RowsNumber; i++)
        {
            for (size_t j = 0; j < M::ColumnsNumber; j++)
            {
                T result = T();

                for (size_t k = 0; k < ColumnsNumber; k++)
                {
                    result += m_data[i][k] * other[k][j];
                }

                matrix[i][j] = result;
            }
        }

        return matrix;
    }

    Row operator*(const Row& other) const
    {
        static_assert(ColumnsNumber == Row::Size, "Trying");
        Row vector;

        for (size_t i = 0; i < RowsNumber; i++)
        {
            for (size_t j = 0; j < Row::Size; j++)
            {
                T result = T();

                for (size_t k = 0; k < ColumnsNumber; k++)
                {
                    result += m_data[i][k] * other[k];
                }

                vector[i] = result;
            }
        }

        return vector;
    }

    const Row& operator[](size_t i) const
    {
        assert(i < RowsNumber && "Index out of bounds");
        return m_data[i];
    }

    Row& operator[](size_t i)
    {
        assert(i < RowsNumber && "Index out of bounds");
        return m_data[i];
    }

private:
    static Matrix MakeIdentityMatrix()
    {
        Matrix identity;
        for (size_t i = 0; i < ColumnsNumber; i++)
        {
            identity[i][i] = T(1.f);
        }
        return identity;
    }

    template<typename M>
    T Determinant(const M& matrix) const
    {
        T result = T();

        for (size_t i = 0; i < M::ColumnsNumber; i++)
        {
            result += matrix[0][i] * Cofactor(0, i);
        }

        return result;
    }

    template<>
    T Determinant(const Matrix<2, 2, T>& matrix) const
    {
        return (m_data[0][0] * m_data[1][1]) - (m_data[0][1] * m_data[1][0]);
    }

private:

    MatrixArray m_data;
};

