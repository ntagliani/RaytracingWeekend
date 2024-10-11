#include "Bvh.h"
#include "Mesh.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <cstdint>

void Bvh::initialize(const Mesh& mesh)
{
  const auto & meshTriangles =  mesh.triangles();
  std::vector<uint32_t> triangleIndices(meshTriangles.size(), 0);
  std::iota(triangleIndices.begin(), triangleIndices.end(), 0);




}
