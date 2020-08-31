#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace Constants
{
    constexpr float Epsilon = 1.e-5f;
    constexpr float BiasAbove = 1.e-5f;
    constexpr float BiasBelow = 1.e-5f;
    constexpr float Pi = float(M_PI);
    constexpr size_t BouncesCount = 5;
}