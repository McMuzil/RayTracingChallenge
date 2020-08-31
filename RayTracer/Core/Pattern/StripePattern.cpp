#include "RayTracer/Core/Pattern/StripePattern.h"

Vec3D StripePattern::GetColorAt(const Vec3D& position) const
{
    return GetColor(abs(int(floor(position.x))) % 2);
}

std::unique_ptr<ICloneable> StripePattern::Clone() const
{
    StripePattern pattern(*this);
    return std::make_unique<StripePattern>(pattern);
}
