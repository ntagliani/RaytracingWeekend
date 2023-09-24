#pragma once

#include <filesystem>

class Image;
namespace PPMImageSerializer
{
	bool serialize(const Image& image, const std::filesystem::path& path);
}
