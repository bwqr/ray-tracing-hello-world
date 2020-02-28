cmake_minimum_required(VERSION 3.15)
project(render_hello_world)

set(CMAKE_CXX_STANDARD 11)

add_executable(render_hello_world main.cpp Camera.cpp Camera.h Surface.h Sphere.cpp Sphere.h Cube.cpp Cube.h Ray.cpp Ray.h vector.h defs.h IntersectionRecord.h)