#include "Camera.h"
#include "Ray.h"
#include "Hittable.h"
#include "Image.h"
#include "Progress.h"
#include "Progression.h"
#include "UniformRandom.h"

#include <random>

namespace camera_cpp
{

}

Camera::Camera() = default;
void Camera::init(const Point& position, const vec3f& lookDirection, const CameraSettings& settings)
{
	moveAndLook(position, lookDirection);
	m_settings = settings;
	updateSettings();
}

void Camera::lookAt(const Point& target)
{
	m_lookDirection = unit_vector(target - m_position);
}
void Camera::move(const Point& position) 
{
	m_position = position;
}
void Camera::moveAndLook(const Point& position, const Point& target)
{
	move(position);
	lookAt(target);
}

int Camera::width() const
{
	return m_width;
}

int Camera::height() const
{
	return m_height;
}

void Camera::setProgress(Progress* progress)
{
	m_progress = progress;
}

void Camera::render(const Hittable& hittable, Image* outImage) 
{
	if (outImage == nullptr || m_width != outImage->width() || m_height != outImage->height())
		return;

	BiLinearProgression progress({ m_height, m_width });
	if (m_progress != nullptr)
	{
		progress.setValue({0,0});
		m_progress->initialize(progress);
	}

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			const vec3f pixel_pos = m_first_pixel_center + (m_delta_u * static_cast<float>(x)) + (m_delta_v * static_cast<float>(y));
			const auto color = antialias(pixel_pos, hittable);
			//const vec3f direction = pixel_pos - m_position;
			//const Ray r{ m_position, direction };

			//const auto color = rayColor(r, hittable);
			outImage->set(x, y) = color;
		}
		if (m_progress != nullptr)
		{
			progress.setValue({ y + 1, m_width });
			m_progress->update(progress);
		}
	}
	if (m_progress != nullptr)
	{
		progress.setValue({ m_height, m_width });
		m_progress->complete(progress);
	}
}

Color Camera::rayColor(const Ray& r, const Hittable& hittable)const
{
	HitRecord record;
	if (hittable.hit(r, Interval::forwardInfinite, &record))
	{
		return 0.5f * (record.m_normal + 1.0f);
	}

	// fade from white to light blue to simulate the sky
	const vec3 unit_direction = unit_vector(r.direction());
	const float a = 0.5f * (1.0f + unit_direction.y());
	const Color start_color{ 1.0f, 1.0f, 1.0f };
	const Color end_color{ 0.5f, 0.7f, 1.0f };
	return (1.0f - a) * start_color + a * end_color;

}

Color Camera::antialias(const vec3f& pixel_pos, const Hittable& hittable) const
{

	if (m_settings.antialias_samples <= 1)
	{
		const vec3f direction = pixel_pos - m_position;
		const Ray r{ m_position, direction };
		return rayColor(r, hittable);
	}

	static std::random_device rd;  // Will be used to obtain a seed for the random number engine
	static std::minstd_rand  gen(rd());
	static std::uniform_real_distribution<float> dis(-0.5f, 0.5f);


	Color sample;
	for (int i = 0; i < m_settings.antialias_samples; i++)
	{
		const vec3f rand_u = (m_delta_u * scaledUnaryRand(-0.5f, 0.5f));
		const vec3f rand_v = (m_delta_v * scaledUnaryRand(-0.5f, 0.5f));
		const vec3f direction = (pixel_pos + rand_u + rand_v )- m_position;
		const Ray r{ m_position, direction };
		sample += rayColor(r, hittable);
	}
	return sample / static_cast<float>(m_settings.antialias_samples);
	
}

void Camera::updateSettings()
{
	m_width  = m_settings.width;

	m_height = static_cast<int>(m_width / m_settings.aspect_ratio);

	const auto viewport_width = m_settings.viewport_height * m_width / m_height;

	const auto viewport_u = viewport_width * vec3f(1.0f, 0.0f, 0.0f );
	const auto viewport_v = -m_settings.viewport_height * vec3f( 0.0f, 1.0f, 0.0f );

	m_delta_u = viewport_u / static_cast<float>(m_width);
	m_delta_v = viewport_v / static_cast<float>(m_height);

	const auto viewport_upper_left = m_position + m_lookDirection * m_settings.focal_length - (viewport_u / 2.0f) - (viewport_v / 2.0f);
	m_first_pixel_center = viewport_upper_left + (m_delta_u + m_delta_v) / 2.0f;

}

