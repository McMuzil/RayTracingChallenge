#pragma once
#include "memory"

class Object;

namespace Helpers
{
    std::unique_ptr<Object> CreateGlassSphere();
}