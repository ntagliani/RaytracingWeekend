#include "PlyLoader.h"

#include "Mesh.h"

#include <happly.h>

#include <algorithm>

std::unique_ptr<Mesh> import(std::string_view path,
                             std::shared_ptr<Material> material)
{
    return import(std::filesystem::path{path}, material);
}

std::unique_ptr<Mesh> import(std::filesystem::path path,
                             std::shared_ptr<Material> material)
{
    std::ifstream inputStream(path, std::ios::in);
    if (!inputStream.is_open())
        return {};

    happly::PLYData plyIn(inputStream);
    const auto& vertexPositions = plyIn.getVertexPositions();
    const auto& plyIndices = plyIn.getFaceIndices();
    std::vector<vec3f> positions;
    std::vector<vec3i> indices;
    std::transform(vertexPositions.begin(), vertexPositions.end(),
                   std::back_inserter(positions),
                   [](const auto& pos)
                   {
                       return vec3f(static_cast<float>(pos[0]),
                                    static_cast<float>(pos[1]),
                                    static_cast<float>(pos[2]));
                   });
    std::transform(
        plyIndices.begin(), plyIndices.end(), std::back_inserter(indices),
        [](const auto& idx)
        {
            return vec3i(static_cast<int>(idx[0]), static_cast<int>(idx[1]),
                         static_cast<int>(idx[2]));
        });

    auto mesh = std::make_unique<Mesh>(positions, indices, material);
    return mesh;
}
