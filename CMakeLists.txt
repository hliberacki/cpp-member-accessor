cmake_minimum_required (VERSION 3.18)
project(Accessor LANGUAGES CXX)

include(GNUInstallDirs)

set(library_name accessor)
add_library(${library_name} INTERFACE)
target_include_directories(${library_name} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

install(TARGETS accessor EXPORT ${library_name}Config
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}) # For Windows

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp*")

install(EXPORT ${library_name}Config DESTINATION share/${library_name}/cmake)

export(TARGETS accessor FILE ${library_name}Config.cmake)

#EXAMPLES
if(${EXAMPLES})
  set (CMAKE_CXX_STANDARD 14)

  add_executable(accessFunctions examples/access_function.cpp)
  target_link_libraries(accessFunctions accessor)
  set_target_properties(accessFunctions PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)

  add_executable(accessMembers examples/access_member.cpp)
  target_link_libraries(accessMembers accessor)
  set_target_properties(accessMembers PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)

  add_executable(accessColletion examples/multiple_instances.cpp)
  target_link_libraries(accessColletion accessor)
  set_target_properties(accessColletion PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)

  add_executable(accessNoMacro examples/no_macro.cpp)
  target_link_libraries(accessNoMacro accessor)
  set_target_properties(accessNoMacro PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)
endif()

#TESTS
enable_testing()
include(CTest)

set(TEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/tests/test_utils)

set(TEST_SOURCES
    tests/functionWrapperTestSuite.cpp
    tests/memberWrapperTestSuite.cpp
    tests/callFunctionTestSuite.cpp
    tests/accessMemberTestSuite.cpp
)

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE accessor)
    target_include_directories(${test_name} PRIVATE ${TEST_INCLUDE_DIR})

    if(MSVC)
        target_compile_options(${test_name} PRIVATE /W4 /WX)
    else()
        target_compile_options(${test_name} PRIVATE -Wall -Wextra -Werror)

         # Suppress known GCC false positive on -Warray-bounds
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_compile_options(${test_name} PRIVATE -Wno-array-bounds)
        endif()
    endif()


    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
