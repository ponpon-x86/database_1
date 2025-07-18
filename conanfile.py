from conan import ConanFile


class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("libpqxx/7.10.1")

    def build_requirements(self):
        self.tool_requires("cmake/3.22.6")