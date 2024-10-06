#pragma once

#include "Mesh.h"
#include <filesystem>
#include <memory>

/// import a ply file type into a mesh object
std::unique_ptr<Mesh> import(std::string_view path,
                             std::shared_ptr<Material> material);
std::unique_ptr<Mesh> import(std::filesystem::path path,
                             std::shared_ptr<Material> material);
