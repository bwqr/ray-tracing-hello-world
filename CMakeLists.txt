cmake_minimum_required(VERSION 3.15)
project(render_hello_world)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -O2")

add_executable(render_hello_world main.cpp Camera.h Surface.h Sphere.cpp Sphere.h vector.cpp vector.h Ray.h defs.h IntersectionRecord.h Light.h Triangle.cpp Triangle.h GlazedSphere.cpp GlazedSphere.h TransparentSphere.cpp TransparentSphere.h)

add_executable(test test.cpp Camera.h Surface.h Sphere.cpp Sphere.h vector.cpp vector.h Ray.h defs.h IntersectionRecord.h Light.h Triangle.cpp Triangle.h GlazedSphere.cpp GlazedSphere.h TransparentSphere.cpp TransparentSphere.h)