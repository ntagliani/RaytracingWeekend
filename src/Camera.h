#pragma once

#include "Vec3.h"

class Hittable;
class Image;
class Ray;
class Progress;

struct CameraSettings
{
    float focal_length = 1.0;
    float aspect_ratio = 16.0f / 9;
    float viewport_height = 2.0f;
    int width = 1024;
    int antialias_samples = 10;
};

class Camera
{
  public:
    Camera();
    void init(const Point& position, const vec3f& lookDirection,
              const CameraSettings& settings);
    void setProgress(Progress* p);
    void lookAt(const Point& position);
    void move(const Point& position);
    void moveAndLook(const Point& position, const Point& target);
    Ray generateRay(int x, int y) const;
    void fillRay(Ray& out, int x, int y) const;

    void render(const Hittable& hittable, Image* outImage);
    int width() const;
    int height() const;
    Color rayColor(const Ray& r, const Hittable& hittable,
                   int max_bounces) const;

  private:
    Color antialias(const vec3f& pixel_pos, const Hittable& hittable) const;
    void updateSettings();

    CameraSettings m_settings;
    Point m_position{0, 0, 0};
    vec3f m_lookDirection{0, 0, -1};
    int m_width{0};
    int m_height{0};

    vec3f m_delta_u;
    vec3f m_delta_v;
    vec3f m_first_pixel_center;

    Progress* m_progress = nullptr;
};
