cmake_minimum_required(VERSION 3.0.0)
project(client-library-test LANGUAGES CXX)

configure_file(../3rdparty/googletest/CMakeLists.txt.in ../3rdparty/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../3rdparty/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../3rdparty/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

set (Sources
  GameBoardTest.cpp
)

add_executable(client-library-test ${Sources})
target_link_libraries(client-library-test PUBLIC gmock_main loderunner-client-library)

add_test(NAME client-library-test COMMAND client-library-test)