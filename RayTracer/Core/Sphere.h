#pragma once

#include "Matrix.h"
#include "Object.h"
#include "Vector.h"

class Sphere : public Object
{
public:

    const Matrix<4, 4>& GetTransform() const { return m_transform; }
    void SetTransform(const Matrix<4, 4>& transform) { m_transform = transform; }

private:

    Matrix<4, 4> m_transform = Matrix<4, 4>::Identity();
};