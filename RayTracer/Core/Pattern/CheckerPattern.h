#pragma once
#include "Core/Pattern/Pattern.h"

class CheckerPattern : public Pattern
{
public:
    using Pattern::Pattern;

    Vec3D GetColorAt(const Vec3D& position) const override;

    std::unique_ptr<ICloneable> Clone() const override;

private:
    float Floor(float f) const;
};