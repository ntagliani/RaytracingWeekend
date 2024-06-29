# Project definition
cmake_minimum_required(VERSION 3.12)
project(RaytracingWeekend)

# Version
set(CoreLib_VERSION_MAJOR 0)
set(CoreLib_VERSION_MINOR 1)
set(CoreLib_VERSION_RELEASE 0)

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

if(MSVC)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /DCORELIB_DEBUG /DWINDOWS /WX")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DCORELIB_DEBUG /DWINDOWS /WX")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /DWINDOWS /WX")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DWINDOWS /WX")
else()
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCORELIB_DEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCORELIB_DEBUG")
  # set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG") set(CMAKE_CXX_FLAGS_RELEASE
  # "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
endif()

if(NOT OPENGL_SUPPORT)
  set(CONAN_EXTRA_PARAMS ${CONAN_EXTRA_PARAMS} -o "corelib:opengl_support=False")
endif()

if(UNIX)
  add_compile_options("-Werror")
endif(UNIX)

if(APPLE)
  set(CMAKE_MACOSX_RPATH OFF)
endif(APPLE)

# configure_file( "${PROJECT_SOURCE_DIR}/src/version.h.in" "${PROJECT_BINARY_DIR}/version.h" )
add_subdirectory(src)
