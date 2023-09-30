#include "Camera.h"
#include "Ray.h"
#include "Hittable.h"
#include "Image.h"

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

void Camera::render(const Hittable& hittable, Image* outImage) 
{
	if (outImage == nullptr || m_width != outImage->width() || m_height != outImage->height())
		return;

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			const vec3f pixel_pos = m_first_pixel_center + (m_delta_u * static_cast<float>(x)) + (m_delta_v * static_cast<float>(y));
			const vec3f direction = pixel_pos - m_position;
			const Ray r{ m_position, direction };

			const auto color = rayColor(r, hittable);
			outImage->set(x, y) = color;
		}
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

