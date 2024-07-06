#pragma once

#include "Vec3.h"

#include <memory>

class Material;

class HitRecord {
public:
  float m_ray_distance;
  Point m_hit_point;
  vec3f m_normal;
  std::weak_ptr<Material> m_hit_material;
};
