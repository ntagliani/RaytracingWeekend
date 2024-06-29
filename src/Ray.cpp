#include "Ray.h"

Ray::Ray(Point origin, vec3f direction)
:m_origin(origin), m_direction(direction)
{}

const Point& Ray::origin() const
{
	return m_origin;
}

const vec3f& Ray::direction() const
{
	return m_direction;
}

void Ray::setOrigin(const Point& origin)
{
	m_origin = origin;
}

void Ray::setDirection(const vec3f& direction)
{
	m_direction = direction;
}

Point Ray::at(float t) const
{
	return m_origin + m_direction * t;
}
