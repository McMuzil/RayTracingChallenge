#pragma once
#include <cstdlib>
#include <limits>
#include <vector>
#include <algorithm>

#include "Core/Constants.h"

namespace Helpers
{
    inline bool IsEqualWithEpsilon(float first, float second, float epsilon = Constants::Epsilon)
    {
        return abs(first - second) < epsilon;
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
};
