#include <fstream>

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

inline void writePixel(std::ofstream& out, const Color& color)
{
    out << static_cast<int>(255.999f * linearToGamma(color.x())) << ' '
        << static_cast<int>(255.999f * linearToGamma(color.y())) << ' '
        << static_cast<int>(255.999f * linearToGamma(color.z())) << '\n';
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
    std::ofstream outFile(path, std::ios::trunc);
    outFile << "P3\n" << image.width() << ' ' << image.height() << "\n255\n";
    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            const auto& pixel = image.get(x, y);
            writePixel(outFile, pixel);
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
    return true;
}
} // namespace PPMImageSerializer