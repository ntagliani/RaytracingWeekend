#pragma once
#include "Hittable.h"


class Sphere : public Hittable
{
public:
	Sphere(Point center, float radius);
	~Sphere() override;

	bool hit(const Ray& r, float ray_min, float ray_max, HitRecord* record) const override;

private:
	Point m_center;
	float m_radius;
};
