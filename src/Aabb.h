#pragma once

#include "Ray.h"
#include "Vec3.h"

#include <limits>

/// Axis aligned bounding box
class Aabb
{
  public:
    Aabb();
    Aabb(vec3f min, vec3f max);
    vec3f min() const;
    vec3f max() const;
    vec3f extent() const;

    bool contains(const vec3f& v) const;
    bool intersect(const Ray& ray) const;

    void growToInclude(const vec3f& v);

    bool empty() const;

  private:
    vec3f m_min{std::numeric_limits<float>::infinity(),
                std::numeric_limits<float>::infinity(),
                std::numeric_limits<float>::infinity()};
    vec3f m_max{-std::numeric_limits<float>::infinity(),
                -std::numeric_limits<float>::infinity(),
                -std::numeric_limits<float>::infinity()};
};
