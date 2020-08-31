#include "RayTracer/Core/Camera.h"

#include "Canvas.h"
#include "Lighting.h"
#include "Ray.h"

Camera::Camera(const Vec2Du& size, float fov)
    : m_size(size)
    , m_fov(fov)
{
    Recalculate();
}

Ray Camera::Raycast(const Vec2Du& coords) const
{
    const Vec2D offset((coords.x + 0.5f) * m_pixelSize, (coords.y + 0.5f) * m_pixelSize);
    const Vec3D worldPos(m_halfSize - offset, -1);
    const Matrix<4, 4> transformInversed = m_transform.Inverse();
    const Vec3D pixel = transformInversed * worldPos.AsPoint();
    const Vec3D origin = transformInversed * Vec3D(0.f).AsPoint();
    const Vec3D direction = (pixel - origin).Normalize();

    return Ray(origin, direction);
}

Ray Camera::Raycast(size_t x, size_t y) const
{
    return Raycast(Vec2Du(x, y));
}

Canvas Camera::Render(const World& world) const
{
    Canvas image(m_size);

    for (size_t y = 0; y < m_size.y; y++)
    {
        for (size_t x = 0; x < m_size.x; x++)
        {
            Ray ray = Raycast(x, y);
            Vec3D color = Lighting::Calculate(world, ray);
            image.SetPixel(color, x, y);
        }
    }

    return image;
}

void Camera::Recalculate()
{
    const float halfView = tan(Helpers::ToRad(m_fov) / 2.f);
    const float aspectRatio = float(m_size.x) / float(m_size.y);
    if (aspectRatio >= 1.f)
    {
        m_halfSize.x = halfView;
        m_halfSize.y = halfView / aspectRatio;
    }
    else
    {
        m_halfSize.x = halfView * aspectRatio;
        m_halfSize.y = halfView;
    }
    m_pixelSize = m_halfSize.x * 2.f / GetSize().x;
}
