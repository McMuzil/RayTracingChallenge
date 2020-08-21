#pragma once
#include "Pattern.h"

class StripePattern : public Pattern
{
public:
    using Pattern::Pattern;

    Vec3D GetColorAt(const Vec3D& position) const override;

    std::unique_ptr<ICloneable> Clone() const override;
};