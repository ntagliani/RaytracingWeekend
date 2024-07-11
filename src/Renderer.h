#pragma once

#include "Vec3.h"

class Camera;
class Hittable;
class Progress;
class Ray;

class RenderTarget
{
  public:
    virtual ~RenderTarget() = default;
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual void setColor(int x, int y, const Color& c) = 0;
};

class Renderer
{
  public:
    void setProgress(Progress* p);
    void render(const Camera& camera, const Hittable& hitable,
                RenderTarget& target);

  private:
    void updateSettings(const Camera& camera, const RenderTarget& target);
    Color antialias(const vec3f& camear_pos, const vec3f& pixel_pos,
                    const Hittable& hittable) const;
    Color rayColor(const Ray& r, const Hittable& hittable,
                   int max_bounces) const;

    vec3f m_delta_u;
    vec3f m_delta_v;
    vec3f m_first_pixel_center;
    int m_antialias_samples = 16;

    Progress* m_progress = nullptr;
};
