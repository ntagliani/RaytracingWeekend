#include "Aabb.h"

#include <array>
#include <memory>
#include <vector>

class Mesh;
class Ray;

class Bvh
{
  public:
    void initialize(const Mesh& mesh);
    bool intersect(const Ray& r) const;

  private:
    struct BvhNode
    {
        Aabb box;
        std::vector<int> triangles;
        std::array<std::unique_ptr<BvhNode>, 2> children;
    };

    std::unique_ptr<BvhNode> m_root;
};
