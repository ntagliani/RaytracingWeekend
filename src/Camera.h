#pragma once

#include "Vec3.h"

#include <vector>

class Hittable;
class Image;
class Ray;

struct CameraSettings
{
	float focal_length = 1.0;
	float aspect_ratio = 16.0f/9;
	float viewport_height = 2.0f;
	int width = 1024;
};

class Camera
{
public:
	
	Camera();
	void init(const Point& position, const vec3f& lookDirection, const CameraSettings& settings);
	void lookAt(const Point& position);
	void move(const Point& position);
	void moveAndLook(const Point& position, const Point& target);

	void render(const Hittable& hittable, Image* outImage);
	int width() const;
	int height() const;
	Color rayColor(const Ray& r, const Hittable& hittable)const;

private:
	void updateSettings();
	CameraSettings m_settings;
	Point m_position{ 0,0,0 };
	vec3f m_lookDirection{ 0,0,-1 };
	int m_width{0};
	int m_height{0};

	vec3f m_delta_u;
	vec3f m_delta_v;
	vec3f m_first_pixel_center;
};