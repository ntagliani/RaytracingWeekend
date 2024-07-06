#pragma once

#include "Material.h"
#include "Vec3.h"

class LambertianMaterial : public Material
{
  public:
    LambertianMaterial(const Color &albedo);
    ~LambertianMaterial();
    bool scatter(const Ray &, const HitRecord &, Color &,
                 Ray &scattered) const override;

  private:
    Color m_albedo;
};
