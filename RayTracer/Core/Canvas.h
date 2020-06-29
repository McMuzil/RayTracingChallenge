#pragma once
#include <vector>

#include "Vector.h"

class Canvas
{
public:
    using PixelRow = std::vector<Vec4D>;
    using PixelArray = std::vector<PixelRow>;

public:
    Canvas();
    Canvas(size_t width, size_t height);
    Canvas(const Vec2Du& size);

    size_t GetWidth() const { return m_size.x; }
    size_t GetHeight() const { return m_size.y; }
    Vec2Du GetSize() const { return m_size; }

    const Vec4D GetPixel(size_t x, size_t y) const;
    const Vec4D GetPixel(const Vec2Du& coords) const;
    void SetPixel(const Vec4D& color, size_t x, size_t y);
    void SetPixel(const Vec4D& color, const Vec2Du& coords);

    const PixelArray& GetPixels() const { return m_pixels; }

    std::string ToPPM() const;

private:
    std::string GetPPMHeader() const;
    std::string GetPPMContent() const;

private:
    Vec2Du m_size;
    PixelArray m_pixels;
};