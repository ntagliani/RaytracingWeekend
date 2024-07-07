
#pragma once
#include "Hittable.h"

#include <memory>
#include <optional>

class Material;

class Mesh : public Hittable
{
  public:
    Mesh(const std::vector<vec3f> vertices, const std::vector<vec3f> triangles,
         std::shared_ptr<Material> material);
    ~Mesh() override;

    bool hit(const Ray& r, const Interval& interval,
             HitRecord* record) const override;

  private:
    std::optional<float> rayIntersectsTriangle(const Ray& r,
                                               const int triangleIndex) const;

    std::vector<vec3f> m_vertices;
    std::vector<vec3f> m_triangles;
    std::vector<vec3f> m_normals;

    std::shared_ptr<Material> m_material;
};
