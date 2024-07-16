#include "Camera.h"

Camera::Camera() = default;
void Camera::init(const Point& position, const vec3f& lookDirection,
                  const CameraSettings& settings)
{
    moveAndLook(position, lookDirection);
    m_settings = settings;
}

void Camera::lookAt(const Point& target)
{
    m_lookDirection = unit_vector(target - m_position);
}
void Camera::move(const Point& position) { m_position = position; }
void Camera::moveAndLook(const Point& position, const Point& target)
{
    move(position);
    lookAt(target);
}

vec3f Camera::lookDirection() const { return m_lookDirection; }
float Camera::focalLength() const { return m_focalLength; }
float Camera::viewportHeight() const { return m_viewportHeight; }
Point Camera::position() const { return m_position; }
