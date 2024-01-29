cmake_minimum_required(VERSION 3.27)
project(test_1)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(test_1 main.cpp)
target_link_libraries(test_1 ${SDL2_LIBRARIES})
