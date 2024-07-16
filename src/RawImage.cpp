#include "RawImage.h"

RawImage::RawImage(int widht, int height) : m_width(widht), m_height(height)
{
    m_buffer.resize(widht * height, Pixel{});
}

RawImage::~RawImage() = default;

int RawImage::width() const { return m_width; }
int RawImage::height() const { return m_height; }

const Pixel& RawImage::get(int x, int y) const
{
    return m_buffer[y * m_width + x];
}

void RawImage::setColor(int x, int y, const Color& c)
{
    const_cast<Color&>(static_cast<const RawImage*>(this)->get(x, y)) = c;
}
