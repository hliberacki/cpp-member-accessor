# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: 2025 Hubert Liberacki
#
# Conan recipe for cpp-member-accessor (header-only C++ library)

from conan import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import cmake_layout, CMake
from conan.tools.build import check_min_cppstd

class CppMemberAccessorConan(ConanFile):
    name = "cpp-member-accessor"
    version = "0.2"
    license = "MIT"
    url = "https://github.com/hliberacki/cpp-member-accessor"
    topics = ("c++", "templates", "access-private-members", "header-only")

    settings = "os", "arch", "compiler", "build_type"

    exports_sources = (
        "CMakeLists.txt",
        "include/*",
        "tests/*",
    )

    no_copy_source = True
    generators = "CMakeToolchain", "CMakeDeps"
    package_type = "header-library"
    exports = "LICENSE"

    def validate(self):
        check_min_cppstd(self, 14)

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure(variables={"BUILD_TESTING": "ON"})
        cmake.build()
        if not self.conf.get("tools.build:skip_test", default=False):
            cmake.test()

    def package(self):
        copy(self, "*.hpp", self.source_folder, self.package_folder)
    
    def package_info(self):
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []

    def package_id(self):
        self.info.clear()
