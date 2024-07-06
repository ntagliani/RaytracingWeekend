#pragma once

#include "Vec3.h"

class Image
{
  public:
    virtual ~Image() = default;

    virtual size_t width() const = 0;
    virtual size_t height() const = 0;
    virtual const Pixel &get(int x, int y) const = 0;
    virtual Pixel &set(int x, int y) = 0;
};
