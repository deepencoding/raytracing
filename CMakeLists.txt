cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(raytracing VERSION 1.0)
add_executable(raytracing src/main.cpp)
target_include_directories(raytracing PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
