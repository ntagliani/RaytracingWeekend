#pragma once
#include "hittable.h"


class Sphere : public Hittable
{
public:
	Sphere(Point center, float radius);
	~Sphere() override;

	bool hit(const Ray& r, const Interval& interval, HitRecord* record) const override;

private:
	Point m_center;
	float m_radius;
};
