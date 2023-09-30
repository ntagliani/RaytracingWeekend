#pragma once

#include "Ray.h"
#include "Interval.h"

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

	virtual bool hit(const Ray& r, const Interval& interval, HitRecord* record) const = 0;
};
