cmake_minimum_required(VERSION 3.0.0)

project(loderunner-client LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost 1.67 REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

if(WIN32)
    add_compile_options(/utf-8)
endif(WIN32)

add_subdirectory(CodeBattleCppLibrary)

add_executable(loderunner-client CodeBattleCpp.cpp)
target_link_libraries(loderunner-client loderunner-client-library Boost::boost OpenSSL::SSL OpenSSL::Crypto)
if(UNIX)
    target_link_libraries(loderunner-client pthread)
endif(UNIX)