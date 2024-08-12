#include "MetalMaterial.h"
#include "HitRecord.h"
#include "Vec3.h"

inline vec3f reflect(const vec3f& inDirection, const vec3f& normal)
{
    return inDirection - 2 * dot(inDirection, normal) * normal;
}

MetalMaterial::MetalMaterial(const Color& albedo, const float fuzzyness)
    : m_albedo(albedo)
    , m_fuzzyness(fuzzyness < 1.0f ? fuzzyness : 1.0f)
{
}

bool MetalMaterial::scatter(const Ray& inRay, const HitRecord& hitRecord,
                            Color& color, Ray& scattered) const
{
    vec3f reflected = reflect(inRay.direction(), hitRecord.m_normal);
    reflected =
        unit_vector(reflected) + (m_fuzzyness * random_unit_vector<float>());
    scattered = Ray(hitRecord.m_hit_point, reflected);
    color = m_albedo;
    return dot(scattered.direction(), hitRecord.m_normal) > 0;
}
