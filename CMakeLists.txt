cmake_minimum_required(VERSION 3.15)
project(render_hello_world)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -fopenmp")

file(GLOB BASE_SRC "Camera.h" "defs.h" "IntersectionRecord.h" "Light.h" "Ray.h" "vector.h" "shapes/sphere/*.h" "shapes/sphere/*.cpp" "shapes/sphere/*.h" "shapes/triangle/*.cpp" "surfaces/*.h" "surfaces/*.cpp")

add_executable(render_hello_world main.cpp ${BASE_SRC})

add_executable(test_render test/test.cpp ${BASE_SRC})