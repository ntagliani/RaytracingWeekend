
#pragma once
#include "Aabb.h"
#include "Hittable.h"

#include <memory>
#include <optional>

class Material;

class Mesh : public Hittable
{
  public:
    Mesh(std::vector<vec3f> vertices, std::vector<vec3i> triangles,
         std::shared_ptr<Material> material);
    ~Mesh() override;

    bool hit(const Ray& r, const Interval& interval,
             HitRecord* record) const override;

    const std::vector<vec3f>& vertices() const;
    const std::vector<vec3i>& triangles() const;
    const std::vector<vec3f>& normals() const;

  private:
    std::optional<float> rayIntersectsTriangle(const Ray& r,
                                               const int triangleIndex) const;

    std::vector<vec3f> m_vertices;
    std::vector<vec3i> m_triangles;
    std::vector<vec3f> m_normals;

    std::vector<std::vector<int>> m_vertex_to_triangle;
    std::shared_ptr<Material> m_material;
    Aabb m_aabb;
};
