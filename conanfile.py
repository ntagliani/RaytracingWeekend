from conan import ConanFile

class RaytracingWeekend(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("happly/cci.20200822")
        # self.requires("gtest/1.15.0")

