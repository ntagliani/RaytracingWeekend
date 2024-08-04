#include "Renderer.h"
#include "Camera.h"
#include "HitRecord.h"
#include "Hittable.h"
#include "Material.h"
#include "Progress.h"
#include "Progression.h"
#include "Ray.h"
#include "TaskManager.h"

#include <chrono>

void Renderer::setProgress(Progress* p) { m_progress = p; }
void Renderer::updateSettings(const Camera& camera, const RenderTarget& target)
{
    const auto height = target.height();
    const auto width = target.width();

    const auto aspect_ratio = static_cast<float>(width) / height;

    const auto viewport_width = camera.viewportHeight() * width / height;

    const auto viewport_u = viewport_width * vec3f(1.0f, 0.0f, 0.0f);
    const auto viewport_v = -camera.viewportHeight() * vec3f(0.0f, 1.0f, 0.0f);

    m_delta_u = viewport_u / static_cast<float>(width);
    m_delta_v = viewport_v / static_cast<float>(height);

    const auto viewport_upper_left =
        camera.position() + camera.lookDirection() * camera.focalLength() -
        (viewport_u / 2.0f) - (viewport_v / 2.0f);
    m_first_pixel_center = viewport_upper_left + (m_delta_u + m_delta_v) / 2.0f;
}

Color Renderer::antialias(const vec3f& camera_position, const vec3f& pixel_pos,
                          const Hittable& hittable) const
{

    if (m_antialias_samples <= 1)
    {
        const vec3f direction = pixel_pos - camera_position;
        const Ray r{camera_position, direction};
        return rayColor(r, hittable, 20);
    }

    static std::random_device
        rd; // Will be used to obtain a seed for the random number engine
    static std::minstd_rand gen(rd());
    static std::uniform_real_distribution<float> dis(-0.5f, 0.5f);

    Color sample;
    for (int i = 0; i < m_antialias_samples; i++)
    {
        const vec3f rand_u = (m_delta_u * dis(gen));
        const vec3f rand_v = (m_delta_v * dis(gen));
        const vec3f direction = (pixel_pos + rand_u + rand_v) - camera_position;
        const Ray r{camera_position, direction};
        sample += rayColor(r, hittable, 10);
    }
    return sample / static_cast<float>(m_antialias_samples);
}

Color Renderer::rayColor(const Ray& r, const Hittable& hittable,
                         int max_bounces) const
{
    HitRecord record;
    if (max_bounces == 0)
        return Color(0.0f, 0.0f, 0.0f);

    if (hittable.hit(r, Interval::toForwardInfinity(0.001f), &record))
    {
        Ray scattered({0, 0, 0}, {0, 0, 0});
        Color attenuation;
        auto material = record.m_hit_material.lock();
        if (material->scatter(r, record, attenuation, scattered))
            return attenuation * rayColor(scattered, hittable, max_bounces - 1);
        return Color(0.0f, 0.0f, 0.0f);
    }

    // fade from white to light blue to simulate the sky
    const vec3 unit_direction = unit_vector(r.direction());
    const float a = 0.5f * (1.0f + unit_direction.y());
    const Color start_color{1.0f, 1.0f, 1.0f};
    const Color end_color{0.5f, 0.7f, 1.0f};
    return (1.0f - a) * start_color + a * end_color;
}

void Renderer::render(const Camera& camera, const Hittable& hittable,
                      RenderTarget& target)
{
    const auto height = target.height();
    const auto width = target.width();

    if (height == 0 || width == 0)
        return;

    updateSettings(camera, target);

    BiLinearProgression progress({height, width});
    if (m_progress != nullptr)
    {
        progress.setValue({0, 0});
        m_progress->initialize(progress);
    }

    TaskManager tm;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            const vec3f pixel_pos = m_first_pixel_center +
                                    (m_delta_u * static_cast<float>(x)) +
                                    (m_delta_v * static_cast<float>(y));
            std::function<void()> f = [pixel_pos, x, y, this, &hittable,
                                       &target, &camera]() -> void
            {
                const auto color =
                    antialias(camera.position(), pixel_pos, hittable);

                target.setColor(x, y, color);
            };
            tm.AddTask(f);
        }
        if (m_progress != nullptr)
        {
            progress.setValue({y + 1, width});
            m_progress->update(progress);
        }
    }
    if (m_progress != nullptr)
    {
        progress.setValue({height, width});
        m_progress->complete(progress);
    }
    while (!tm.areAllDone())
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(10ms);
    }
}
