cmake_minimum_required(VERSION 3.0.0)

project(loderunner-client-library LANGUAGES CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(Sources
  BoardElement.h

  BoardPoint.cpp
  BoardPoint.h

  GameBoard.h
  GameBoard.cpp

  GameClientLodeRunner.h
  GameClientLodeRunner.cpp

  LoderunnerAction.h
  LodeRunnerBlocks.h
  PlayerAction.h
)

add_subdirectory(easywsclient)
add_library(loderunner-client-library ${Sources})
target_include_directories(loderunner-client-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(loderunner-client-library PUBLIC easywsclient)