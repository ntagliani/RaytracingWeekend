#pragma once

#include "Material.h"

class MetalMaterial : public Material
{
  public:
    MetalMaterial(const Color& albedo, float fuzzyness);
    virtual ~MetalMaterial() = default;
    virtual bool scatter(const Ray&, const HitRecord&, Color&,
                         Ray& scattered) const;

  private:
    Color m_albedo;
    float m_fuzzyness;
};
