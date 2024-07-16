#pragma once

#include "Renderer.h"
#include "Vec3.h"

class Image : public RenderTarget
{
  public:
    virtual ~Image() = default;

    virtual const Pixel& get(int x, int y) const = 0;
};
