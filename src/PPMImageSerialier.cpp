#pragma once

#include <fstream>

#include "PPMImageSerializer.h"
#include "Image.h"
#include "vec3.h"

namespace PPMImageSerializer
{
	bool serialize(const Image& image, const std::filesystem::path& path)
	{
		std::ofstream outFile(path, std::ios::trunc);
		outFile << "P3\n" << image.width() << ' ' << image.height() << "\n255\n";
		for (int y = 0; y < image.height(); y++)
		{
			for (int x = 0; x < image.width(); x++)
			{
				auto& pixel = image.get(x, y);
				outFile << static_cast<int>(255.999f * pixel.x()) << ' ' 
					<< static_cast<int>(255.999f * pixel.y()) << ' ' << 
					static_cast<int>(255.999f * pixel.z()) << '\n';
			}
		}
		return true;
	}
}