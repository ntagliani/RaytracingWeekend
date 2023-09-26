#include "Sphere.h"


Sphere::Sphere(Point center, float radius)
: m_center(std::move(center))
, m_radius(radius){
}

Sphere::~Sphere() = default;

bool Sphere::hit(const Ray& ray, float ray_min, float ray_max, HitRecord* record) const
{
	// (- b + -sqrt(b ^ 2 - 4ac)) / 2a
// b^2 >= 4ac
// (x - center)^2 = radius*radius
// x =  raycenter + direction * t
// (raycenter + t_direction - spherecenter)^2 = radius^2

// a = direction * direction
// b = 2direction * (raycenter - spherecenter)
// c = (raycenter - spherecenter)^2 - radius^2
// a 2 factor can be simplified in the quadratic formula

	const auto d = ray.origin() - m_center;
	const auto a = ray.direction().length_squared();
	const auto half_b = dot(ray.direction(), d); // b/2
	const auto c = d.length_squared() - m_radius * m_radius;
	const auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0.0f)
	{
		return false;
	}
	// returns the closest point on the sphere (-b - sqrt(...)) instad of (-b + sqrt(...))
	const auto sqrt_discriminant = sqrt(discriminant);
	auto root = (-half_b - sqrt_discriminant) / a;
	if (root < ray_min || root > ray_max)
	{
		root = (-half_b + sqrt_discriminant) / a;
		if (root < ray_min || root > ray_max)
			return false;
	}

	if (record != nullptr)
	{
		auto& r = *record;
		r.m_ray_distance = root;
		r.m_hit_point = ray.at(root);
		r.m_normal = (record->m_hit_point - m_center) / m_radius;
	}
	return true;
}
