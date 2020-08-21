#include "Core/Pattern/PatternFactory.h"

PatternFactory::PatternFactory()
{
}

PatternFactory* PatternFactory::Get()
{
    assert(m_factory.get() && "Factory is nullptr");
    return m_factory.get();
}

void PatternFactory::Set(std::unique_ptr<PatternFactory>&& factory)
{
    m_factory = std::move(factory);
}

std::unique_ptr<PatternFactory> PatternFactory::m_factory = nullptr;
