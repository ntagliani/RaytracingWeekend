#pragma once

#include "vec3.h"

class Ray
{
public:
	Ray(Point origin, vec3f direction);
	const Point& origin() const;
	const vec3f& direction() const;
	Point at(float t) const;

private:
	Point m_origin;
	vec3f m_direction;

};
