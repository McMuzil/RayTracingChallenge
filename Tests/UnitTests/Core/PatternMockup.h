#pragma once

#include "RayTracer/Core/Pattern/Pattern.h"

class PatternMockup : public Pattern
{
public:
    using Pattern::Pattern;

    Vec3D GetColorAt(const Vec3D& position) const override
    {
        return position;
    }

    std::unique_ptr<ICloneable> Clone() const override
    {
        PatternMockup pattern(*this);
        return std::make_unique<PatternMockup>(pattern);
    }
};