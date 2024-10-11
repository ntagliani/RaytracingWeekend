# Project definition
cmake_minimum_required(VERSION 3.24)
project(RaytracingWeekend LANGUAGES CXX)

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

set(CMAKE_CXX_STANDARD 20)

#include(CacheVariables)
#include(FilterFunctions)

find_package(happly)
find_package(GTest REQUIRED)

add_executable(RaytracingDemo)
add_custom_command(TARGET RaytracingDemo POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/testdata/ $<TARGET_FILE_DIR:RaytracingDemo> COMMENT "Copying test data to output folders $<TARGET_FILE_DIR:RaytracingDemo>")

add_executable(TestRaytracing)

target_link_libraries(TestRaytracing happly::happly gtest::gtest)
target_link_libraries(RaytracingDemo happly::happly)

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
  src/Aabb.cpp
  src/Aabb.h
  src/Bvh.cpp
  src/Bvh.h
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
  src/LambertianMaterial.cpp
  src/LambertianMaterial.h
  src/Material.h
  src/Mesh.cpp
  src/Mesh.h
  src/MetalMaterial.cpp
  src/MetalMaterial.h
  src/PlyLoader.cpp
  src/PlyLoader.h
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

target_sources(RaytracingDemo PRIVATE ${SOURCES} src/main.cpp)

set(TESTSOURCES
  tests/testAabb.cpp
)
target_include_directories(TestRaytracing PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_sources(TestRaytracing PRIVATE ${SOURCES} ${TESTSOURCES} tests/testmain.cpp)

