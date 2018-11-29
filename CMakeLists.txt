cmake_minimum_required (VERSION 3.0)
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

  add_executable(accessMembers examples/access_member.cpp)
  target_link_libraries(accessMembers accessor)

  add_executable(accessColletion examples/multiple_instances.cpp)
  target_link_libraries(accessColletion accessor)

  add_executable(accessNoMacro examples/no_macro.cpp)
  target_link_libraries(accessNoMacro accessor)
endif()

#TESTS
enable_testing()
add_executable(functionWrapperTestSuite tests/functionWrapperTestSuite.cpp)
target_link_libraries(functionWrapperTestSuite accessor)

add_executable(memberWrapperTestSuite tests/memberWrapperTestSuite.cpp)
target_link_libraries(memberWrapperTestSuite accessor)

add_executable(callFunctionTestSuite tests/callFunctionTestSuite.cpp)
target_link_libraries(callFunctionTestSuite accessor)

add_executable(accessMemberTestSuite tests/accessMemberTestSuite.cpp)
target_link_libraries(accessMemberTestSuite accessor)

add_test(functionWrapperTests functionWrapperTestSuite)
add_test(memberWrapperTests memberWrapperTestSuite)
add_test(callFunctionTest callFunctionTestSuite)
add_test(accessMemberTest accessMemberTestSuite)
