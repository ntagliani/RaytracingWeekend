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
    void lookAt(const Point& position);
    void move(const Point& position);
    void moveAndLook(const Point& position, const Point& target);

    Point position() const;
    vec3f lookDirection() const;
    float focalLength() const;
    float viewportHeight() const;

  private:
    float m_focalLength = 1.0f;
    float m_viewportHeight = 2.0f;

    CameraSettings m_settings;
    Point m_position{0, 0, 0};
    vec3f m_lookDirection{0, 0, -1};
};
