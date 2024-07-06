#pragma once

#include "Ray.h"
#include "Vec3.h"

class HitRecord;

class Material {
public:
  virtual ~Material() = default;
  virtual bool scatter(const Ray &, const HitRecord &, Color &,
                       Ray &scattered) const = 0;
};
