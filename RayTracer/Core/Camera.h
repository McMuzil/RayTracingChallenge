#pragma once
#include "Matrix.h"
#include "Vector.h"

class Canvas;
class Ray;
class World;

class Camera
{
public:
    Camera(const Vec2Du& size, float fov = 90.f);

    Vec2Du GetSize() const { return m_size; }
    void SetSize(Vec2Du val) { m_size = val; Recalculate(); }

    float GetFOV() const { return m_fov; }
    void SetFOV(float val) { m_fov = val; Recalculate(); }

    float GetPixelSize() const { return m_pixelSize; }

    Matrix<4, 4> GetTransform() const { return m_transform; }
    void SetTransform(Matrix<4, 4> val) { m_transform = val; }

    Ray Raycast(size_t x, size_t y) const;
    Ray Raycast(const Vec2Du& coords) const;

    Canvas Render(const World& world) const;

private:
    void Recalculate();

private:
    Matrix<4, 4> m_transform = Matrix<4, 4>::Identity();

    Vec2Du m_size;
    Vec2D m_halfSize;

    float m_fov = 0.f; // Degree
    float m_pixelSize = 0.f;
};