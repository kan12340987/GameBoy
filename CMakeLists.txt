cmake_minimum_required(VERSION 3.16)
project(gbemu VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(gbemu src/emu_core.cpp)
target_link_libraries(gbemu ${SDL2_LIBRARIES})