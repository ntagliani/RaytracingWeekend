#pragma once

#include "Interval.h"
#include "Ray.h"

class HitRecord;

class Hittable {
public:
  virtual ~Hittable() = default;

  virtual bool hit(const Ray &r, const Interval &interval,
                   HitRecord *record) const = 0;
};
