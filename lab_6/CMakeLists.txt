cmake_minimum_required(VERSION 3.10)
set(SubProjectName "lab_6")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${SubProjectName}_lib src/druid.cpp src/npc.cpp src/orc.cpp src/slave_trader.cpp src/logger/console_logger.cpp src/logger/file_logger.cpp src/logger/ILogger.cpp)
add_executable(${SubProjectName}_exe main.cpp)

target_link_libraries(${SubProjectName}_exe PRIVATE ${SubProjectName}_lib)

add_executable(${SubProjectName}_tests tests/test.cpp)
target_link_libraries(${SubProjectName}_tests ${SubProjectName}_lib gtest_main)

add_test(NAME {SubProjectName}_Tests COMMAND ${SubProjectName}_tests)