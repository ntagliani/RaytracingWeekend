#include "MetalMaterial.h"
#include "HitRecord.h"
#include "Vec3.h"

inline vec3f reflect(const vec3f& inDirection, const vec3f& normal)
{
    return inDirection - 2 * dot(inDirection, normal) * normal;
}

MetalMaterial::MetalMaterial(const Color& albedo) : m_albedo(albedo) {}

bool MetalMaterial::scatter(const Ray& inRay, const HitRecord& hitRecord,
                            Color& color, Ray& scattered) const
{
    const vec3f reflected = reflect(inRay.direction(), hitRecord.m_normal);
    scattered = Ray(hitRecord.m_hit_point, reflected);
    color = m_albedo;
    return true;
}
