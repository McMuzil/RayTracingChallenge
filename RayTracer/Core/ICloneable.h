#pragma once
#include "Helpers.h"

class ICloneable
{
public:
    virtual std::unique_ptr<ICloneable> Clone() const = 0;
};

template<typename A, typename B = A>
std::unique_ptr<B> Clone(std::unique_ptr<A>& ptr)
{
    return Helpers::template StaticCastPtr<B, ICloneable>(ptr->Clone());
}

template<typename A, typename B = A>
std::unique_ptr<B> Clone(A* ptr)
{
    return Helpers::template StaticCastPtr<B, ICloneable>(ptr->Clone());
}

template<typename A, typename B = A>
std::unique_ptr<B> Clone(A& ptr)
{
    return Helpers::template StaticCastPtr<B, ICloneable>(ptr.Clone());
}
