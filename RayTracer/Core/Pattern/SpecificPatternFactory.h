#pragma once
#include "PatternFactory.h"

class Pattern;

class SpecificPatternFactory : public PatternFactory
{
public:
    SpecificPatternFactory();

protected:
    std::unique_ptr<Pattern> CreateInternal(const std::string& type, const Vec3D& colorA, const Vec3D& colorB) const override;
};