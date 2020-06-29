#pragma once
#include <cstdlib>
#include <limits>

#include "Core/Constants.h"

namespace Helpers
{
    inline bool IsEqualWithEpsilon(float first, float second, float epsilon = Constants::Epsilon)
    {
        return abs(first - second) < epsilon;
    }
};