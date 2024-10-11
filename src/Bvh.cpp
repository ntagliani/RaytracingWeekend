#include "Bvh.h"
#include "Mesh.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <cstdint>
#include <span>

void build(std::span<uint32_t> indices, const Aabb& currentBoundingBox,const std::span<const vec3f> trianglesBarycenters, const std::span<const vec3f>  vertices )
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

}


void Bvh::initialize(const Mesh& mesh)
{
  const auto& meshTriangles =  mesh.triangles();
  const auto& meshVertices = mesh.vertices();
  std::vector<uint32_t> triangleIndices(meshTriangles.size(), 0);
  
  Aabb aabb;
  for (const auto& vertex: meshVertices)
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

    trianglesBarycenters[trIndex] = barycenter/3.0f;
  }

}


