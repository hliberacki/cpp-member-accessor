cmake_minimum_required(VERSION 3.18)
project(PackageTest CXX)

find_package(cpp-member-accessor CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example PRIVATE cpp-member-accessor::cpp-member-accessor)
