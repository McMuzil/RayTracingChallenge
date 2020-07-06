#pragma once

#include <iostream>

#include "Core/Vector.h"
#include "Core/Matrix.h"

int main()
{
    Matrix<4, 4> empty;
    Matrix<4, 4> empty1{ { 1.f } };
    Matrix<4, 4> empty2{ { 1.f }, { 1.f } };
    Matrix<4, 4> empty3{ { 1.f }, { 1.f }, { 1.f } };
    Matrix<4, 4> empty4{ { 1.f }, { 1.f }, { 1.f }, { 1.f } };

    Matrix<2, 2> w({ 1.f });
    Matrix<3, 3> m(
        { 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f }
        );
    Vec2D vec;

    std::cout << vec << std::endl;

    return 0;
}