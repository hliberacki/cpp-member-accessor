cmake_minimum_required (VERSION 3.6)
project(Accessor)

add_library(accessor INTERFACE)
target_sources(accessor INTERFACE include/accessor.hpp)
target_include_directories(accessor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/include/
         DESTINATION include/accessor
         FILES_MATCHING PATTERN "*.hpp*")


set (CMAKE_CXX_STANDARD 14)
add_executable(accessorUsage tests/main.cpp)
