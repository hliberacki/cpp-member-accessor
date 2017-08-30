cmake_minimum_required (VERSION 3.6)
project(Accessor)

add_library(accessor INTERFACE)

target_include_directories(accessor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/src/
         DESTINATION include/accessor
         FILES_MATCHING PATTERN "*.hpp*")


set (CMAKE_CXX_STANDARD 17)
add_executable(accessorUsage tests/main.cpp)
