#pragma once

#include <filesystem>

class Image;
class Progress;
namespace PPMImageSerializer
{
bool serialize(const Image &image, const std::filesystem::path &path,
               Progress *progress = nullptr);
}
