cmake_minimum_required(VERSION 3.0.0)

project(easywsclient LANGUAGES CXX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(easywsclient easywsclient.cpp)
target_include_directories(easywsclient INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})