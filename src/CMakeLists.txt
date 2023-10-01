set(SOURCES
	Camera.cpp
	Camera.h
	ConsoleProgressBar.cpp
	ConsoleProgressBar.h
    Hittable.h
    HittableCollection.cpp
    HittableCollection.h
    Image.h
    Interval.h
    main.cpp
    PPMImageSerialier.cpp
    PPMImageSerializer.h
	Progress.h
	Progression.h
    RawImage.cpp
    RawImage.h
    Ray.cpp
    Ray.h
    Sphere.cpp
    Sphere.h
    Vec3.h)

add_executable(RaytracingDemo ${SOURCES})
