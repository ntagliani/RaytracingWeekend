#include "Vec3.h"

class Camera;

class RenderTarget
{
    virtual ~RenderTarget() = default;
    virtual size_t width() const = 0;
    virtual size_t height() const = 0;
    virtual void setColor(int x, int y, const Color &c) = 0;
};

class Renderer
{
    void render(const Camera &camera, RenderTarget &target);
};