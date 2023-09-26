#include "RawImage.h"

RawImage::RawImage(int widht, int height)
	: m_width(widht)
	, m_height(height) {
	m_buffer.resize(widht * height, Pixel{});
}

RawImage::~RawImage() = default;

size_t RawImage::width() const
{
	return m_width;
}
size_t RawImage::height() const
{
	return m_height;
}

const Pixel& RawImage::get(int x, int y) const
{
	return m_buffer[y * m_width + x];
}

Pixel& RawImage::set(int x, int y)
{
	return const_cast<Pixel&>(static_cast<const RawImage*>(this)->get(x, y));
}
