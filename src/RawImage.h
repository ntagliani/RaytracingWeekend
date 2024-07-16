#pragma once

#include "Image.h"
#include "Vec3.h"

#include <vector>

class RawImage : public Image
{
  public:
    RawImage(int widht, int height);
    ~RawImage() override;

    int width() const override;
    int height() const override;
    const Pixel& get(int x, int y) const override;
    void setColor(int x, int y, const Color& c) override;

  private:
    int m_width{0};
    int m_height{0};
    std::vector<Pixel> m_buffer;
};
