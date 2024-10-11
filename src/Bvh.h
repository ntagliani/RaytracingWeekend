#include "Aabb.h"

#include <array>
#include <memory>
#include <vector>

class Mesh;

class Bvh
{
  public:
    void initialize(const Mesh& mesh);

  private:
    struct BvhNode
    {
        Aabb box;
        std::vector<int> triangles;
        std::array<std::unique_ptr<BvhNode>, 2> children;
    };

    std::unique_ptr<BvhNode> m_root;
};
