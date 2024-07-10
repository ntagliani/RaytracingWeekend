#include <cstdio>
#include <fstream>
#include <vector>

#include "CommonDefines.h"
#include "Image.h"
#include "PPMImageSerializer.h"
#include "Progress.h"
#include "Progression.h"
#include "Vec3.h"

namespace PPMImageSerializer
{
template <typename T> T linearToGamma(T in)
{
    if (in > T(0))
        return std::sqrt(in);
    return T(0);
}
template <typename... Args>
inline int localSprintf(char* buffer, size_t bufferSize, const char* fmt,
                        Args... args)
{
#ifdef WIN32
    return snprintf(buffer, bufferSize, fmt, args...);
#else
    return snprintf(buffer, bufferSize, fmt, args...);
#endif
}

inline size_t pixelToBuffer(char* buffer, size_t bufferSize, const Color& color)
{

    return localSprintf(buffer, bufferSize, "%d %d %d\n",
                        static_cast<int>(255.999f * linearToGamma(color.x())),
                        static_cast<int>(255.999f * linearToGamma(color.y())),
                        static_cast<int>(255.999f * linearToGamma(color.z())));
}

bool serialize(const Image& image, const std::filesystem::path& path,
               Progress* progress)
{
    BiLinearProgression progression(
        {static_cast<int>(image.height()), static_cast<int>(image.width())});
    if (progress != nullptr)
    {
        progression.setValue({0, 0});
        progress->initialize(progression);
    }
    const size_t headerSize = 22;
    const size_t pixelSize = 13;
    const size_t totalMemoryBuffer =
        headerSize + (image.width() * image.height() * pixelSize);
    std::vector<char> buffer;
    buffer.resize(totalMemoryBuffer);
    size_t offset = localSprintf(
        &buffer[0], totalMemoryBuffer, "P3\n%d %d\n255\n",
        static_cast<int>(image.width()), static_cast<int>(image.height()));

    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            const auto& pixel = image.get(x, y);
            offset += pixelToBuffer(&buffer[offset], totalMemoryBuffer - offset,
                                    pixel);
        }
        if (progress != nullptr)
        {
            progression.setValue({y + 1, static_cast<int>(image.height())});
            progress->update(progression);
        }
    }
    if (progress != nullptr)
    {
        progression.setValue({static_cast<int>(image.height()),
                              static_cast<int>(image.width())});
        progress->complete(progression);
    }

    std::ofstream outFile(path, std::ios::trunc);
    outFile.write(buffer.data(), offset);
    return true;
}
} // namespace PPMImageSerializer
