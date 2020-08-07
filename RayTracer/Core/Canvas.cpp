#include "Core/Canvas.h"

#include <algorithm>
#include <sstream>

namespace
{
    const Vec4D CanvasDefaultPixelColor(0.f, 0.f, 0.f, 1.f);
    const int MinPPMColorNumber = 0;
    const int MaxPPMColorNumber = 255;
}

Canvas::Canvas()
    : Canvas(Vec2Du(0))
{

}

Canvas::Canvas(size_t width, size_t height)
    : Canvas(Vec2Du(width, height))
{
}

Canvas::Canvas(const Vec2Du& size)
    : m_size(size)
{
    const std::vector<Vec4D> innerVec(size.x, CanvasDefaultPixelColor);
    m_pixels.resize(size.y, innerVec);
}

const Vec4D Canvas::GetPixel(size_t x, size_t y) const
{
    return GetPixel(Vec2Du(x, y));
}

const Vec4D Canvas::GetPixel(const Vec2Du& coords) const
{
    assert(coords < m_size);
    return m_pixels[coords.y][coords.x];
}

void Canvas::SetPixel(const Vec4D& color, size_t x, size_t y)
{
    SetPixel(color, Vec2Du(x, y));
}

void Canvas::SetPixel(const Vec4D& color, const Vec2Du& coords)
{
    assert(coords < m_size);
    m_pixels[coords.y][coords.x] = color;
}

std::string Canvas::ToPPM() const
{
    std::string result;
    result += GetPPMHeader();
    result += GetPPMContent();

    return result;
}

std::string Canvas::GetPPMHeader() const
{
    std::stringstream ss;
    ss << "P3" << std::endl;
    ss << m_size << std::endl;
    ss << MaxPPMColorNumber << std::endl;

    return ss.str();
}

std::string Canvas::GetPPMContent() const
{
    std::stringstream ss;

    for (size_t y = 0; y < m_size.y; y++)
    {
        for (size_t x = 0; x < m_size.x; x++)
        {
            const Vec4D rgba = m_pixels[y][x] * MaxPPMColorNumber;
            const Vec4Di rgbaUnsigned(
                int(round(rgba.r)), 
                int(round(rgba.g)),
                int(round(rgba.b)),
                int(round(rgba.a))
            );
            const Vec4Du rgbaUnsignedClamped(
                std::clamp(rgbaUnsigned.r, MinPPMColorNumber, MaxPPMColorNumber),
                std::clamp(rgbaUnsigned.g, MinPPMColorNumber, MaxPPMColorNumber),
                std::clamp(rgbaUnsigned.b, MinPPMColorNumber, MaxPPMColorNumber),
                std::clamp(rgbaUnsigned.a, MinPPMColorNumber, MaxPPMColorNumber)
            );

            // TODO: for now we ignore Alpha component
            const Vec3Du rgb(rgbaUnsignedClamped.r, rgbaUnsignedClamped.g, rgbaUnsignedClamped.b);

            ss << rgb;

            assert(m_size.x != 0u);
            if (x != m_size.x - 1u)
            {
                ss << " ";
            }
        }

        ss << std::endl;
    }

    return ss.str();
}
