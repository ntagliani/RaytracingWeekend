#include "Aabb.h"

#include <cmath>

vec3f Aabb::min() const
{
    return m_min;
}
vec3f Aabb::max() const
{
    return m_max;
}

bool Aabb::contains(const vec3f& v) const
{
    if (empty())
        return false;

    return m_min <= v && v <= m_max;
}

bool Aabb::intersect(const Ray& ray) const
{
    const auto& origin = ray.origin();
    if (contains(origin))
        return true;

    const auto& invDir = ray.inverseDirection();
    float tmin = 0.0f;
    float tmax = std::numeric_limits<float>::infinity();

    for (int dimension = 0; dimension < 3; dimension++)
    {
        const bool sign = std::signbit(invDir[dimension]);
        const float bmin = (sign ? m_max : m_min)[dimension];
        const float bmax = (sign ? m_min : m_max)[dimension];

        const float dmin = (bmin - origin[dimension]) * invDir[dimension];
        const float dmax = (bmax - origin[dimension]) * invDir[dimension];

        tmin = std::max(dmin, tmin);
        tmax = std::min(dmax, tmax);
    }

    return tmin < tmax;
}

vec3f Aabb::extent() const
{
    return m_max - m_min;
}

void Aabb::growToInclude(const vec3f& v)
{
    if (empty())
    {
        m_min = v;
        m_max = v;
    }
    else
    {
        m_min[0] = std::min(m_min[0], v[0]);
        m_min[1] = std::min(m_min[1], v[1]);
        m_min[2] = std::min(m_min[2], v[2]);

        m_max[0] = std::max(m_max[0], v[0]);
        m_max[1] = std::max(m_max[1], v[1]);
        m_max[2] = std::max(m_max[2], v[2]);
    }
}

bool Aabb::empty() const
{
    return m_max < m_min;
}
