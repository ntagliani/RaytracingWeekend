#include <iostream>

#include "RawImage.h"
#include "Vec3.h"
#include "PPMImageSerializer.h"
#include "Hittable.h"
#include "HittableCollection.h"
#include "Sphere.h"
#include "Camera.h"

int main(int argc, char** argv)
{
	std::cout << "Preparing Image" << std::endl;

	const vec3f camera_position{ 0,0,0 };
	const vec3f look_direction{ 0,0,-1.0f };

	// default settings
	CameraSettings settings{ /* focal_length = */ 1.0f, /*aspect_ratio =*/ 16.0f / 9, /* viewport_heigh = */ 2.0f , /*image_width = */ 1024};
	Camera camera;
	camera.init(camera_position, look_direction, settings);

	RawImage image{ camera.width(), camera.height()};


	HittableCollection collection;
	collection.addHittable(std::make_unique<Sphere>(Point{ 0.0f, 0.0f, -10.0f }, 4.0f));
	collection.addHittable(std::make_unique<Sphere>(Point{ 5.0f, 0.0f, -12.0f }, 2.0f));
	
	camera.render(collection, &image);
	
	std::cout << "Serializing Image" << std::endl;

	if (PPMImageSerializer::serialize(image, "test.ppm"))
	{
		std::cout << "Done" << std::endl;
	}
	else {
		std::cout << "ERROR" << std::endl;
	}

	return 0;
}