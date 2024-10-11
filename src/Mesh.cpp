#include "Mesh.h"
#include "HitRecord.h"

Mesh::Mesh(std::vector<vec3f> vertices, std::vector<vec3i> triangles,
           std::shared_ptr<Material> material)
    : m_vertices(std::move(vertices))
    , m_triangles(std::move(triangles))
    , m_material(material)
{
    m_normals.reserve(m_triangles.size());

    for (const auto& vertex : m_vertices)
    {
        m_aabb.growToInclude(vertex);
    }

    m_vertex_to_triangle.resize(m_vertices.size());
    for (int trIndex = 0; trIndex < m_triangles.size(); trIndex++)
    {
        auto& tr = m_triangles[trIndex];

        m_vertex_to_triangle[tr.x()].push_back(trIndex);
        m_vertex_to_triangle[tr.y()].push_back(trIndex);
        m_vertex_to_triangle[tr.z()].push_back(trIndex);

        const auto& v1 = m_vertices[tr.x()];
        const auto& v2 = m_vertices[tr.y()];
        const auto& v3 = m_vertices[tr.z()];
        const auto d1 = v2 - v1;
        const auto d2 = v3 - v1;
        m_normals.emplace_back(cross(d1, d2).normalize());
    }
}

Mesh::~Mesh() = default;

const std::vector<vec3f>& Mesh::vertices() const
{
    return m_vertices;
}

const std::vector<vec3i>& Mesh::triangles() const
{
    return m_triangles;
}

const std::vector<vec3f>& Mesh::normals() const
{
    return m_normals;
}

bool Mesh::hit(const Ray& ray, const Interval& interval,
               HitRecord* record) const
{
    if (!m_aabb.intersect(ray))
        return false;

    for (int i = 0; i < m_triangles.size(); ++i)
    {
        const auto intersection = rayIntersectsTriangle(ray, i);
        if (intersection.has_value())
        {
            if (interval.excludes(*intersection))
                return false;
            if (record != nullptr)
            {
                auto& r = *record;
                r.m_ray_distance = *intersection;
                r.m_hit_point = ray.at(*intersection);
                r.m_normal = m_normals[i];
                r.m_hit_material = m_material;
            }
            return true;
        }
    }
    return false;
}

/// Triangle-ray intersection taken out of wikipedia
std::optional<float> Mesh::rayIntersectsTriangle(const Ray& r,
                                                 const int triangleIndex) const
{
    constexpr float epsilon = 1e-6f;

    const auto& tr = m_triangles[triangleIndex];

    const auto& v1 = m_vertices[tr.x()];
    const auto& v2 = m_vertices[tr.y()];
    const auto& v3 = m_vertices[tr.z()];

    const auto edge1 = v2 - v1;
    const auto edge2 = v3 - v1;

    const auto ray_cross_e2 = cross(r.direction(), edge2);
    const float det = dot(edge1, ray_cross_e2);

    if (det > -epsilon && det < epsilon)
        return {};

    const float inv_det = 1.0f / det;
    const vec3f s = r.origin() - v1;
    const float u = inv_det * dot(s, ray_cross_e2);
    if (u < 0 || u > 1)
        return {};
    const vec3 s_cross_e1 = cross(s, edge1);
    const float v = inv_det * dot(r.direction(), s_cross_e1);
    if (v < 0 || u + v > 1)
        return {};

    const float t = inv_det * dot(edge2, s_cross_e1);
    if (t > epsilon)
        return t;
    return {};
}
