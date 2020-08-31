#pragma once
#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <limits>
#include <memory>
#include <vector>

#include "RayTracer/Core/Constants.h"

namespace Helpers
{
    inline bool IsEqualWithEpsilon(float first, float second, float epsilon = Constants::Epsilon)
    {
        return abs(first - second) < epsilon;
    }

    inline float ToRad(float degree)
    {
        return degree * Constants::Pi / 180.f;
    }

    inline float ToDegree(float rad)
    {
        return rad * 180.f / Constants::Pi;
    }

    template<typename T>
    typename std::vector<T>::iterator InsertSorted(std::vector<T>& vec, T const& item)
    {
        return vec.insert
        (
            std::upper_bound(vec.begin(), vec.end(), item),
            item
        );
    }

    template<typename ToType, typename FromType>
    std::unique_ptr<ToType> StaticCastPtr(std::unique_ptr<FromType>& base)
    {
        FromType* p = base.release();
        assert(dynamic_cast<ToType*>(p));

        return std::unique_ptr<ToType>(static_cast<ToType*>(p));
    }

    template<typename ToType, typename FromType>
    std::unique_ptr<ToType> StaticCastPtr(std::unique_ptr<FromType>&& base)
    {
        FromType* p = base.release();
        assert(dynamic_cast<ToType*>(p));

        return std::unique_ptr<ToType>(static_cast<ToType*>(p));
    }
}
