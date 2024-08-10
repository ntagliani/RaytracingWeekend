# Project definition
cmake_minimum_required(VERSION 3.12)
project(RaytracingWeekend)

# Version
# set(CoreLib_VERSION_MAJOR 0)
# set(CoreLib_VERSION_MINOR 1)
# set(CoreLib_VERSION_RELEASE 0)

# PROJECT_BINARY_DIR --> path from where the cmake command is executed

# PROJECT_SOURCE_DIR --> path where CMakeLists.txt shall be found

# include cmake files from the cmake folder
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Compiler flags
set(CMAKE_VERBOSE_MAKEFILE ON)

# generate the command commands exports
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

#include(CacheVariables)
#include(FilterFunctions)

add_executable(RaytracingDemo)

if(MSVC)
  add_compile_options("/WX /W4")
else()
  add_compile_options("-Werror -Wall")
endif()

if (WIN32)
  target_compile_definitions(RaytracingDemo PUBLIC WIN_PLATFORM)
endif()

if(UNIX AND NOT APPLE)
  target_compile_definitions(RaytracingDemo PUBLIC UNIX_PLATFORM)
endif()

if(APPLE)
  set(CMAKE_MACOSX_RPATH OFF)
  target_compile_definitions(RaytracingDemo PUBLIC APPLE_PLATFORM)
endif()

set(SOURCES
	src/Camera.cpp
	src/Camera.h
	src/ConsoleProgressBar.cpp
	src/ConsoleProgressBar.h
  src/CommonDefines.h
  src/HitRecord.h
  src/Hittable.h
  src/HittableCollection.cpp
  src/HittableCollection.h
  src/Image.h
  src/Interval.h
  src/main.cpp
  src/LambertianMaterial.cpp
  src/LambertianMaterial.h
  src/Material.h
  src/Mesh.cpp
  src/Mesh.h
  src/MetalMaterial.cpp
  src/MetalMaterial.h
  src/PPMImageSerialier.cpp
  src/PPMImageSerializer.h
	src/Progress.h
	src/Progression.h
  src/Random.h
  src/RawImage.cpp
  src/RawImage.h
  src/Ray.cpp
  src/Ray.h
  src/Renderer.cpp
  src/Renderer.h
  src/Sphere.cpp
  src/Sphere.h
  src/TaskManager.cpp
  src/TaskManager.h
  src/ThreadName.cpp
  src/ThreadName.h
  src/TaskQueue.h
  src/Vec3.h )

target_sources(RaytracingDemo PRIVATE ${SOURCES})

