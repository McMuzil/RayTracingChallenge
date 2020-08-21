#include "Core/Pattern/CheckerPattern.h"

Vec3D CheckerPattern::GetColorAt(const Vec3D& position) const
{
    float x = abs(Floor(position.x));
    float y = abs(Floor(position.y));
    float z = abs(Floor(position.z));

    float summ = x + y + z;
    return GetColor(int(summ) % 2);
}

std::unique_ptr<ICloneable> CheckerPattern::Clone() const
{
    CheckerPattern pattern = *this;
    return std::make_unique<CheckerPattern>(pattern);
}

float CheckerPattern::Floor(float f) const
{
    float rounded = round(f);
    if (Helpers::IsEqualWithEpsilon(f, rounded))
    {
        return rounded;
    }

    return floor(f);
}
