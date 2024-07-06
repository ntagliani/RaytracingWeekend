#pragma once
#include "Hittable.h"

#include <memory>

class Material;

class Sphere : public Hittable {
public:
  Sphere(Point center, float radius, std::shared_ptr<Material> material);
  ~Sphere() override;

  bool hit(const Ray &r, const Interval &interval,
           HitRecord *record) const override;

private:
  Point m_center;
  float m_radius;
  std::shared_ptr<Material> m_material;
};
