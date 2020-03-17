cmake_minimum_required(VERSION 3.15)
project(render_hello_world)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -fopenmp")

add_executable(render_hello_world main.cpp Camera.h surface/Surface.h sphere/Sphere.cpp sphere/Sphere.h vector.h Ray.h defs.h IntersectionRecord.h Light.h Triangle.cpp Triangle.h sphere/GlazedSphere.cpp sphere/GlazedSphere.h sphere/TransparentSphere.cpp sphere/TransparentSphere.h surface/TransparentSurface.cpp surface/TransparentSurface.h surface/GlazedSurface.cpp surface/GlazedSurface.h surface/DiffusedSurface.cpp surface/DiffusedSurface.h sphere/DiffusedSphere.h sphere/DiffusedSphere.cpp)

add_executable(test test.cpp Camera.h surface/Surface.h sphere/Sphere.cpp sphere/Sphere.h vector.h Ray.h defs.h IntersectionRecord.h Light.h Triangle.cpp Triangle.h sphere/GlazedSphere.cpp sphere/GlazedSphere.h sphere/TransparentSphere.cpp sphere/TransparentSphere.h)