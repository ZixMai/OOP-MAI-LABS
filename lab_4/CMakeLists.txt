cmake_minimum_required(VERSION 3.10)
set(SubProjectName "lab_4")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${SubProjectName}_lib src/Figure.tpp src/FigureArray.tpp src/Point.tpp src/Rhombus.tpp src/Trapezoid.tpp src/Pentagon.tpp)
set_target_properties(${SubProjectName}_lib PROPERTIES LINKER_LANGUAGE CXX)
add_executable(${SubProjectName}_exe main.cpp)

target_link_libraries(${SubProjectName}_exe PRIVATE ${SubProjectName}_lib)

add_executable(${SubProjectName}_tests tests/tests.cpp)
target_link_libraries(${SubProjectName}_tests ${SubProjectName}_lib gtest_main)

add_test(NAME {SubProjectName}_Tests COMMAND ${SubProjectName}_tests)