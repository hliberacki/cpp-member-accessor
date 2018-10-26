cmake_minimum_required (VERSION 3.0)
project(Accessor)

add_library(accessor INTERFACE)
target_sources(accessor INTERFACE include/accessor.hpp)
target_include_directories(accessor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

INSTALL (DIRECTORY ${CMAKE_SOURCE_DIR}/include/
         DESTINATION include/accessor
         FILES_MATCHING PATTERN "*.hpp*")

#EXAMPLES
if(${EXAMPLES})
  set (CMAKE_CXX_STANDARD 14)

  add_executable(accessFunctions examples/access_function.cpp)
  add_executable(accessMembers examples/access_member.cpp)
  add_executable(accessColletion examples/multiple_instances.cpp)
  add_executable(accessNoMacro examples/no_macro.cpp)
endif()

#TESTS
enable_testing()
add_executable(functionWrapperTestSuite tests/functionWrapperTestSuite.cpp)
add_executable(memberWrapperTestSuite tests/memberWrapperTestSuite.cpp)
add_executable(callFunctionTestSuite tests/callFunctionTestSuite.cpp)
add_executable(accessMemberTestSuite tests/accessMemberTestSuite.cpp)

add_test(functionWrapperTests functionWrapperTestSuite)
add_test(memberWrapperTests memberWrapperTestSuite)
add_test(callFunctionTest callFunctionTestSuite)
add_test(accessMemberTest accessMemberTestSuite)
