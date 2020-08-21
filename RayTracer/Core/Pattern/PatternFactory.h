#pragma once
#include "memory"
#include "functional"
#include "assert.h"
#include "unordered_map"
#include "Pattern.h"

class PatternFactory
{
public:
    PatternFactory();

    static PatternFactory* Get();
    static void Set(std::unique_ptr<PatternFactory>&& factory);

    template <class T = Pattern>
    std::unique_ptr<T> Create(const std::string& type, const Vec3D& colorA, const Vec3D& colorB) const
    {
        return Helpers::StaticCastPtr<T>(CreateInternal(type, colorA, colorB));
    }

protected:
    virtual std::unique_ptr<Pattern> CreateInternal(const std::string& type, const Vec3D& colorA, const Vec3D& colorB) const = 0;

    using PatternFunc = std::function<std::unique_ptr<Pattern>(const Vec3D&, const Vec3D&)>;
    std::unordered_map<std::string, PatternFunc> m_patternMap;

private:
    static std::unique_ptr<PatternFactory> m_factory;
};
