from conan import ConanFile
from conan.tools.files import copy

class CppMemberAccessorConan(ConanFile):
    name = "cpp-member-accessor"
    version = "0.2"
    license = "MIT"
    url = "https://github.com/hliberacki/cpp-member-accessor"
    topics = ("c++", "templates", "access-private-members", "header-only")

    settings = None
    exports_sources = "include/*"
    no_copy_source = True
    package_type = "header-library"
    exports = "LICENSE"

    def package(self):
        copy(self, "*.hpp", self.source_folder, self.package_folder)
    
    def package_info(self):
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
