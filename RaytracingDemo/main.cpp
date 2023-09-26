#include <iostream>

#include "RawImage.h"
#include "vec3.h"
#include "Ray.h"
#include "PPMImageSerializer.h"


RawImage generateGradient(int x, int y)
{
	RawImage outputImage{ x, y };
	for (int y = 0; y < outputImage.height(); y++)
	{
		for (int x = 0; x < outputImage.width(); x++)
		{
			auto& p = outputImage.set(x, y);
			p.x() = (1.0f * x / outputImage.width());
			p.y() = (1.0f * y / outputImage.height());
			p.z() = 0.25f;
		}
	}
	return outputImage;
}


float hit_sphere(const Ray& r, const Point& center, float radius)
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

	const auto d = r.origin() - center;
	const auto a = r.direction().length_squared();
	const auto half_b = dot(r.direction(), d); // b/2
	const auto c = d.length_squared() - radius * radius;
	const auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0.0f)
	{
		return -1.0f;
	}
	// returns the closest point on the sphere (-b - sqrt(...)) instad of (-b + sqrt(...))
	return (-half_b - sqrt(discriminant)) / a;
}

Color ray_color(const Ray& r) {
	const vec3f sphere_centre{0.0f, 0.0f, -1.0f};
	const float sphere_radius = 0.5f;
	if (const float hit_distance = hit_sphere(r, sphere_centre, sphere_radius); hit_distance >= 0)
	{
		const auto normal = unit_vector(r.at(hit_distance) - sphere_centre);

		return 0.5f * (normal + 1.0f);
	}
	const vec3 unit_direction = unit_vector(r.direction());
	const float a = 0.5f * (1.0f + unit_direction.y());
	const Color start_color{ 1.0f, 1.0f, 1.0f };
	const Color end_color{ 0.5f, 0.7f, 1.0f };
	return (1.0f - a) * start_color + a * end_color;
}

int main(int argc, char** argv)
{
	std::cout << "Preparing Image" << std::endl;

	const int image_width = 1024;
	const float aspect_ratio = 16.0f / 9;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	const vec3f camera_position{ 0,0,0 };

	const float focal_length = 1.0f;
	const float viewport_height = 2.0f;
	const float viewport_width = viewport_height * image_width / image_height;

	const vec3f viewport_u{ viewport_width, 0.0f, 0.0f };
	const vec3f viewport_v{ 0.0f, -viewport_height, 0.0f };

	const vec3f delta_u = viewport_u / static_cast<float>(image_width);
	const vec3f delta_v = viewport_v / static_cast<float>(image_height);

	const vec3f viewport_upper_left = camera_position + vec3{0.0f, 0.0f, -focal_length} - (viewport_u / 2.0f) - (viewport_v / 2.0f);
	const vec3f first_pixel_center = viewport_upper_left + (delta_u + delta_v) / 2.0f;

	RawImage image{ image_width, image_height };
	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			const vec3f pixel_pos = first_pixel_center + (delta_u * static_cast<float>(x)) + (delta_v * static_cast<float>(y));
			const vec3f direction = pixel_pos - camera_position;
			const Ray r{ camera_position, direction };
			const auto color = ray_color(r);
			image.set(x, y) = color;
		}
	}

	std::cout << "Serializing Image" << std::endl;

	if (PPMImageSerializer::serialize(image, "test.ppm"))
	{
		std::cout << "Done" << std::endl;
	}
	else {
		std::cout << "ERROR" << std::endl;
	}

	return 0;
}