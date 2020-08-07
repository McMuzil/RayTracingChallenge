#pragma once

#include <array>
#include "assert.h"

#include "Core/Constants.h"
#include "Core/Helpers.h"

namespace
{
    #define OutOfRangeErrorDescription "Trying to use a property out of vector's range. | " __FUNCTION__
}

template <class T, size_t N>
class Vector
{
public:
    typedef T type;
    constexpr static size_t Size = N;

public:

    Vector()
    {
        m_data.fill(T());
    }

    ~Vector() = default;

    Vector(T value)
    {
        m_data.fill(value);
    }

    Vector(T x, T y)
        : m_data{ x, y }
    {
    }

    Vector(T x, T y, T z)
        : m_data{ x, y, z }
    {
    }

    Vector(T x, T y, T z, T w)
        : m_data{ x, y, z, w }
    {
    }

    Vector(const std::array<T, N>& vec)
        : m_data(vec)
    {
    }

    Vector(std::array<T, N>&& vec)
        : m_data(std::move(vec))
    {
    }

    Vector(const Vector<T, 4>& vec)
    {
        Init(vec);
    }

    Vector(const Vector<T, 3>& vec)
    {
        Init(vec);
    }

    Vector(const Vector<T, 2>& vec)
    {
        Init(vec);
    }

    Vector(const Vector<T, N - 1>& vec, T value)
    {
        Init(vec);
        m_data.back() = value;
    }

    template <class T, size_t N>
    void Init(const Vector<T, N>& vec)
    {
        m_data.fill(T());
        for (size_t i = 0; i < std::min(Size, vec.Size); i++)
        {
            m_data[i] = vec[i];
        }
    }

    const Vector& operator=(Vector&& other)
    {
        m_data = std::move(other.m_data);
        return *this;
    }

    const Vector& operator=(const Vector& other)
    {
        m_data = other.m_data;
        return *this;
    }

#pragma region X_ALIAS

    __declspec(property(get = GetX, put = SetX)) T x;

    T& GetX()
    {
        return m_data[0];
    }
    T GetX() const
    {
        return m_data[0];
    }
    void SetX(T x)
    {
        m_data[0] = x;
    }

#pragma endregion

#pragma region Y_ALIAS

    __declspec(property(get = GetY, put = SetY)) T y;

    T& GetY()
    {
        static_assert(N > 1, OutOfRangeErrorDescription);
        return m_data[1];
    }
    T GetY() const
    {
        static_assert(N > 1, OutOfRangeErrorDescription);
        return m_data[1];
    }
    void SetY(T y)
    {
        static_assert(N > 1, OutOfRangeErrorDescription);
        m_data[1] = y;
    }

#pragma endregion

#pragma region Z_ALIAS

    __declspec(property(get = GetZ, put = SetZ)) T z;

    T& GetZ()
    {
        static_assert(N > 2, OutOfRangeErrorDescription);
        return m_data[2];
    }
    T GetZ() const
    {
        static_assert(N > 2, OutOfRangeErrorDescription);
        return m_data[2];
    }
    void SetZ(T z)
    {
        static_assert(N > 2, OutOfRangeErrorDescription);
        m_data[2] = z;
    }

#pragma endregion

#pragma region W_ALIAS

    __declspec(property(get = GetW, put = SetW)) T w;

    T& GetW()
    {
        static_assert(N > 3, OutOfRangeErrorDescription);
        return m_data[3];
    }
    T GetW() const
    {
        static_assert(N > 3, OutOfRangeErrorDescription);
        return m_data[3];
    }
    void SetW(T w)
    {
        static_assert(N > 3, OutOfRangeErrorDescription);
        m_data[3] = w;
    }

#pragma endregion

#pragma region R_ALIAS

    __declspec(property(get = GetR, put = SetR)) T r;

    T& GetR()
    {
        return m_data[0];
    }
    T GetR() const
    {
        return m_data[0];
    }
    void SetR(T r)
    {
        m_data[0] = r;
    }

#pragma endregion

#pragma region G_ALIAS

    __declspec(property(get = GetG, put = SetG)) T g;

    T& GetG()
    {
        static_assert(N > 1, OutOfRangeErrorDescription);
        return m_data[1];
    }
    T GetG() const
    {
        static_assert(N > 1, OutOfRangeErrorDescription);
        return m_data[1];
    }
    void SetG(T g)
    {
        static_assert(N > 1, OutOfRangeErrorDescription);
        m_data[1] = g;
    }

#pragma endregion

#pragma region B_ALIAS

    __declspec(property(get = GetB, put = SetB)) T b;

    T& GetB()
    {
        static_assert(N > 2, OutOfRangeErrorDescription);
        return m_data[2];
    }
    T GetB() const
    {
        static_assert(N > 2, OutOfRangeErrorDescription);
        return m_data[2];
    }
    void SetB(T b)
    {
        static_assert(N > 2, OutOfRangeErrorDescription);
        m_data[2] = b;
    }

#pragma endregion

#pragma region A_ALIAS

    __declspec(property(get = GetA, put = SetA)) T a;

    T& GetA()
    {
        static_assert(N > 3, OutOfRangeErrorDescription);
        return m_data[3];
    }
    T GetA() const
    {
        static_assert(N > 3, OutOfRangeErrorDescription);
        return m_data[3];
    }
    void SetA(T a)
    {
        static_assert(N > 3, OutOfRangeErrorDescription);
        m_data[3] = a;
    }

#pragma endregion

    void Set(T x, T y)
    {
        static_assert(N > 1, OutOfRangeErrorDescription);
        m_data = { x, y };
    }

    void Set(T x, T y, T z)
    {
        static_assert(N > 2, OutOfRangeErrorDescription);
        m_data = { x, y, z };
    }

    void Set(T x, T y, T z, T w)
    {
        static_assert(N > 3, OutOfRangeErrorDescription);
        m_data = { x, y, z, w };
    }

    const T* Data() const
    {
        return m_data.data();
    }

    template <class A = T, size_t B = N, typename std::enable_if<!std::is_signed<A>::value, A>::type* = nullptr>
    Vector Abs() const
    {
        return *this;
    }

    template <class A = T, size_t B = N, typename std::enable_if<std::is_signed<A>::value, A>::type* = nullptr>
    Vector Abs() const
    {
        std::array<T, N> vec;

        for (size_t i = 0; i < N; ++i)
        {
            vec[i] = abs(m_data[i]);
        }

        return vec;
    }

    float Length() const
    {
        return sqrt(LengthSq());
    }

    float LengthSq() const
    {
        float magnitude = 0.f;

        for (size_t i = 0; i < N; ++i)
        {
            magnitude += m_data[i] * m_data[i];
        }

        return magnitude;
    }

    Vector Normalize() const
    {
        std::array<T, N> vec;
        const float length = Length();
        assert(!Helpers::IsEqualWithEpsilon(length, 0.f));

        for (size_t i = 0; i < N; ++i)
        {
            vec[i] = m_data[i] / length;
        }

        return vec;
    }

    float Dot(const Vector& other) const
    {
        float result = 0.f;

        for (size_t i = 0; i < N; ++i)
        {
            result += m_data[i] * other.m_data[i];
        }

        return result;
    }

    Vector Cross(const Vector& other) const
    {
        assert(!"Cross product should be implemented for every dimension separately.");
        return Vector();
    }

    Vector<T, N + 1> AsVector() const
    {
        Vector<T, N + 1> vector;

        for (size_t i = 0; i < N; i++)
        {
            vector[i] = m_data[i];
        }

        vector[N] = 0.f;

        return vector;
    }

    Vector<T, N + 1> AsPoint() const
    {
        Vector<T, N + 1> point;

        for (size_t i = 0; i < N; i++)
        {
            point[i] = m_data[i];
        }

        point[N] = 1.f;

        return point;
    }

    static Vector Reflect(const Vector& vec, const Vector& normal)
    {
        return vec - normal * 2.f * vec.Dot(normal);
    }

    static bool IsEqualWithEpsilon(const Vector& first, const Vector& second, float epsilon = Constants::Epsilon)
    {
        const Vector absVec = (first - second).Abs();

        for (size_t i = 0; i < N; ++i)
        {
            if (absVec.m_data[i] > epsilon)
            {
                return false;
            }
        }

        return true;
    }

    bool IsEqualWithEpsilon(const Vector& other, float epsilon = Constants::Epsilon) const
    {
        return Vector::IsEqualWithEpsilon(*this, other, epsilon);
    }

    Vector operator-() const
    {
        std::array<T, N> vec;

        for (size_t i = 0; i < N; ++i)
        {
            vec[i] = -m_data[i];
        }

        return Vector(std::move(vec));
    }

    Vector operator+(const Vector& other) const
    {
        std::array<T, N> vec;

        for (size_t i = 0; i < N; ++i)
        {
            vec[i] = m_data[i] + other.m_data[i];
        }

        return Vector(std::move(vec));
    }

    Vector operator-(const Vector& other) const
    {
        std::array<T, N> vec;

        for (size_t i = 0; i < N; ++i)
        {
            vec[i] = m_data[i] - other.m_data[i];
        }

        return Vector(std::move(vec));
    }

    Vector operator*(const Vector& other) const
    {
        std::array<T, N> vec;

        for (size_t i = 0; i < N; ++i)
        {
            vec[i] = m_data[i] * other.m_data[i];
        }

        return Vector(std::move(vec));
    }

    Vector operator/(const Vector& other) const
    {
        std::array<T, N> vec;

        for (size_t i = 0; i < N; ++i)
        {
            vec[i] = m_data[i] / other.m_data[i];
        }

        return Vector(std::move(vec));
    }

    Vector& operator+=(const Vector& other)
    {
        for (size_t i = 0; i < N; ++i)
        {
            m_data[i] += other.m_data[i];
        }

        return *this;
    }

    Vector& operator-=(const Vector& other)
    {
        for (size_t i = 0; i < N; ++i)
        {
            m_data[i] -= other.m_data[i];
        }

        return *this;
    }

    Vector& operator*=(const Vector& other)
    {
        for (size_t i = 0; i < N; ++i)
        {
            m_data[i] *= other.m_data[i];
        }

        return *this;
    }

    Vector& operator/=(const Vector& other)
    {
        for (size_t i = 0; i < N; ++i)
        {
            m_data[i] /= other.m_data[i];
        }

        return *this;
    }

    Vector& operator+=(T v)
    {
        for (size_t i = 0; i < N; ++i)
        {
            m_data[i] += v;
        }

        return *this;
    }

    Vector& operator-=(T v)
    {
        for (size_t i = 0; i < N; ++i)
        {
            m_data[i] -= v;
        }

        return *this;
    }

    Vector& operator*=(T v)
    {
        for (size_t i = 0; i < N; ++i)
        {
            m_data[i] *= v;
        }

        return *this;
    }

    Vector& operator/=(T v)
    {
        for (size_t i = 0; i < N; ++i)
        {
            m_data[i] /= v;
        }

        return *this;
    }

    bool operator==(const Vector& other) const
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (m_data[i] != other.m_data[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator<(const Vector& other) const
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (m_data[i] >= other.m_data[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator>(const Vector& other) const
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (m_data[i] <= other.m_data[i])
            {
                return false;
            }
        }

        return true;
    }

    const T& operator[](size_t i) const
    {
        assert(i < Size && "Index out of bounds");
        return m_data[i];
    }

    T& operator[](size_t i)
    {
        assert(i < Size && "Index out of bounds");
        return m_data[i];
    }

    friend std::ostream& operator<<(std::ostream& output, const Vector& vector)
    {
        for (size_t i = 0; i < N; ++i)
        {
            output << vector.m_data[i];

            assert(N != 0u);
            if (i != N - 1)
            {
                output << " ";
            }
        }

        return output;
    }

    friend std::istream& operator>>(std::istream& input, const Vector& vector)
    {
        char delimiter;
        for (size_t i = 0; i < N; ++i)
        {
            input >> vector.m_data[i];
            if (i != N - 1)
            {
                input.get(delimiter);
            }
        }
        return input;
    }

private:

    std::array<T, N> m_data;

};

typedef Vector<float, 2> Vec2D;
typedef Vector<float, 3> Vec3D;
typedef Vector<float, 4> Vec4D;

typedef Vector<size_t, 2> Vec2Du;
typedef Vector<size_t, 3> Vec3Du;
typedef Vector<size_t, 4> Vec4Du;

typedef Vector<int, 2> Vec2Di;
typedef Vector<int, 3> Vec3Di;
typedef Vector<int, 4> Vec4Di;

template<>
Vec3D Vec3D::Cross(const Vec3D& other) const
{
    return Vec3D(
        this->y * other.z - this->z * other.y,
        this->z * other.x - this->x * other.z,
        this->x * other.y - this->y * other.x
    );
}

template<>
Vec4D Vec4D::Cross(const Vec4D& other) const
{
    return Vec4D(
        this->y * other.z - this->z * other.y,
        this->z * other.x - this->x * other.z,
        this->x * other.y - this->y * other.x,
        0.f
    );
}