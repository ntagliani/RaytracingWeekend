#include <chrono>
#include <iostream>
#include <memory>

#include "Camera.h"
#include "ConsoleProgressBar.h"
#include "HittableCollection.h"
#include "LambertianMaterial.h"
#include "PPMImageSerializer.h"
#include "RawImage.h"
#include "Sphere.h"
#include "Vec3.h"

int main(int argc, char **argv) {

  std::cout << "Rendering Image" << std::endl;
  const auto startTime = std::chrono::high_resolution_clock::now();

  const vec3f camera_position{0, 0, 0};
  const vec3f look_direction{0, 0, -1.0f};

  ConsoleProgressBar progressBar("Rendering");
  // default settings
  CameraSettings settings{/* focal_length = */ 1.0f,
                          /*aspect_ratio =*/16.0f / 9,
                          /* viewport_heigh = */ 2.0f,
                          /*image_width = */ 400,
                          /*antialias_samples = */ 50};
  Camera camera;
  camera.init(camera_position, look_direction, settings);
  camera.setProgress(&progressBar);

  RawImage image{camera.width(), camera.height()};

  // red Lambertian material
  const auto lambertianMaterial =
      std::make_shared<LambertianMaterial>(Color(1.0f, 0.0, 0.0));
  // soil material (gree-ish)
  const auto soilMaterial =
      std::make_shared<LambertianMaterial>(Color(.2f, 0.8, 0.0));
  HittableCollection collection;
  collection.addHittable(std::make_unique<Sphere>(Point{0.0f, 0.0f, -1.0f},
                                                  0.5f, lambertianMaterial));
  collection.addHittable(std::make_unique<Sphere>(Point{0.8f, 0.0f, -1.35f},
                                                  .35f, lambertianMaterial));
  collection.addHittable(std::make_unique<Sphere>(Point{0.0f, -100.5f, 0.0f},
                                                  100.0f, soilMaterial));

  camera.render(collection, &image);

  std::cout << "Serializing Image" << std::endl;

  ConsoleProgressBar progressBarSerialization("Serializing");
  if (PPMImageSerializer::serialize(image, "test.ppm",
                                    &progressBarSerialization)) {
    std::cout << "Done" << std::endl;
  } else {
    std::cout << "ERROR" << std::endl;
    return 1;
  }

  auto duration = std::chrono::high_resolution_clock::now() - startTime;
  std::cout << "Generation took: " << duration.count() / 1e9 << "s"
            << std::endl;
  return 0;
}
