#pragma once

#include "Ray.h"

class HitRecord
{
public :
	float m_ray_distance;
	Point m_hit_point;
	vec3f m_normal;
};

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& r, float ray_min, float ray_max, HitRecord* record) const = 0;
};
