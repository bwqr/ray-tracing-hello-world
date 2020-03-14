cmake_minimum_required(VERSION 3.15)
project(render_hello_world)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(render_hello_world main.cpp Camera.h Surface.h Sphere.cpp Sphere.h Ray.h vector.h defs.h IntersectionRecord.h Light.h Triangle.cpp Triangle.h)