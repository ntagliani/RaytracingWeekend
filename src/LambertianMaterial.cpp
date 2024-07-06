#include "LambertianMaterial.h"

#include "HitRecord.h"

LambertianMaterial::LambertianMaterial(const Color& albedo) : m_albedo(albedo)
{
}

LambertianMaterial::~LambertianMaterial() = default;

bool LambertianMaterial::scatter(const Ray& ray, const HitRecord& hitRecord,
                                 Color& color, Ray& scattered) const
{

    const auto scatterDirection = [&hitRecord]()
    {
        auto direction = hitRecord.m_normal + vec3f::random().normalize();

        if (direction.near_zero())
            return hitRecord.m_normal;

        return direction;
    }();

    scattered = Ray(hitRecord.m_hit_point, scatterDirection);

    color = m_albedo;

    return true;
}
