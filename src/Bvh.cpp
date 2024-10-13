#include "Bvh.h"
#include "Mesh.h"
#include "Ray.h"

#include <algorithm>
#include <cstdint>
#include <span>
#include <vector>

void build(std::span<uint32_t> indices, const Aabb& currentBoundingBox,
           const std::span<const vec3f> trianglesBarycenters,
           const std::span<const vec3f> vertices,
           const std::span<const vec3i> triangles)
{
    if (indices.size() == 1)
        return;

    const vec3f& extent = currentBoundingBox.extent();

    int max_extent = 0;
    auto extent_value = extent[0];
    for (int direction = 1; direction < 3; ++direction)
    {
        if (extent[direction] > extent_value)
        {
            max_extent = direction;
            extent_value = extent[direction];
        }
    }

    const auto midPoint =
        currentBoundingBox.min()[max_extent] + 0.5f * extent_value;
    auto itSplit = std::partition(
        indices.begin(), indices.end(),
        [midPoint, max_extent, trianglesBarycenters](const uint32_t trIndex)
        {
            return trianglesBarycenters[trIndex][max_extent] < midPoint;
        });

    const auto leftSize = std::distance(indices.begin(), itSplit);

    Aabb leftAABB, rightAABB;
    if (2 * leftSize < indices.size())
    {
        // build left and recover right
        for (auto it = indices.begin(); it != itSplit; it++)
        {
            leftAABB.growToInclude(vertices[triangles[*it][0]]);
            leftAABB.growToInclude(vertices[triangles[*it][1]]);
            leftAABB.growToInclude(vertices[triangles[*it][2]]);
        }
        auto rightMin = currentBoundingBox.min();
        rightMin[max_extent] = leftAABB.max()[max_extent];
        rightAABB = Aabb(rightMin, currentBoundingBox.max());
    }
    else
    {
        // build right and recover left

        for (auto it = itSplit; it != indices.end(); it++)
        {
            rightAABB.growToInclude(vertices[triangles[*it][0]]);
            rightAABB.growToInclude(vertices[triangles[*it][1]]);
            rightAABB.growToInclude(vertices[triangles[*it][2]]);
        }
        auto leftMax = currentBoundingBox.max();
        leftMax[max_extent] = rightAABB.min()[max_extent];
        rightAABB = Aabb(currentBoundingBox.min(), leftMax);
    }

    build(indices.subspan(0, leftSize), leftAABB, trianglesBarycenters,
          vertices, triangles);
    build(indices.subspan(leftSize), rightAABB, trianglesBarycenters, vertices,
          triangles);
}

bool Bvh::intersect(const Ray& r) const
{
    return false;
}

void Bvh::initialize(const Mesh& mesh)
{
    const auto& meshTriangles = mesh.triangles();
    const auto& meshVertices = mesh.vertices();
    std::vector<uint32_t> triangleIndices(meshTriangles.size(), 0);

    Aabb aabb;
    for (const auto& vertex : meshVertices)
    {
        aabb.growToInclude(vertex);
    }
    std::vector<vec3f> trianglesBarycenters(meshTriangles.size());
    for (int trIndex = 0; trIndex < meshTriangles.size(); ++trIndex)
    {
        triangleIndices[trIndex] = trIndex;
        vec3f barycenter{0.0f, 0.0f, 0.0f};

        barycenter += meshVertices[meshTriangles[trIndex][0]];
        barycenter += meshVertices[meshTriangles[trIndex][1]];
        barycenter += meshVertices[meshTriangles[trIndex][2]];

        trianglesBarycenters[trIndex] = barycenter / 3.0f;
    }

    build(triangleIndices, aabb, trianglesBarycenters, meshVertices,
          meshTriangles);
}
