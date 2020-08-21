#include "Core/Pattern/SpecificPatternFactory.h"

#include "CheckerPattern.h"
#include "Core/Vector.h"
#include "Pattern.h"
#include "PatternFactory.h"
#include "StripePattern.h"

SpecificPatternFactory::SpecificPatternFactory()
{
    m_patternMap["Stripe"] = [](const Vec3D& colorA, const Vec3D& colorB) { return std::make_unique<StripePattern>(colorA, colorB); };
    m_patternMap["Checker"] = [](const Vec3D& colorA, const Vec3D& colorB) { return std::make_unique<CheckerPattern>(colorA, colorB); };
}

std::unique_ptr<Pattern> SpecificPatternFactory::CreateInternal(const std::string& type, const Vec3D& colorA, const Vec3D& colorB) const
{
    const auto& it = m_patternMap.find(type);

    assert(it != m_patternMap.cend());
    const PatternFunc& func = it->second;

    return func(colorA, colorB);
}
