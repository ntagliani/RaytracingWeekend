#include <fstream>

#include "PPMImageSerializer.h"
#include "Image.h"
#include "Vec3.h"
#include "Progress.h"
#include "Progression.h"
#include "Interval.h"

namespace PPMImageSerializer
{
	bool serialize(const Image& image, const std::filesystem::path& path, Progress* progress)
	{
		BiLinearProgression progression({ static_cast<int>(image.height()), static_cast<int>(image.width()) });
		if (progress != nullptr)
		{
			progression.setValue({ 0,0 });
			progress->initialize(progression);
		}
		std::ofstream outFile(path, std::ios::trunc);
		outFile << "P3\n" << image.width() << ' ' << image.height() << "\n255\n";
		Interval intensity(0.0f, 0.999f);
		for (int y = 0; y < image.height(); y++)
		{
			for (int x = 0; x < image.width(); x++)
			{
				auto& pixel = image.get(x, y);
				outFile << static_cast<int>(255 * intensity.clamp(pixel.x())) << ' ' 
					<< static_cast<int>(255 * intensity.clamp(pixel.y())) << ' ' << 
					static_cast<int>(255 * intensity.clamp(pixel.z())) << '\n';
			}
			if (progress != nullptr)
			{
				progression.setValue({ y+1,static_cast<int>(image.height())});
				progress->update(progression);
			}
		}
		if (progress != nullptr)
		{
			progression.setValue({ static_cast<int>(image.height()), static_cast<int>(image.width()) });
			progress->complete(progression);
		}
		return true;
	}
}