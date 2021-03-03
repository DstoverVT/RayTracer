cmake_minimum_required(VERSION 3.5)
project(RayTracer CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/lib)

set(LIB
  ${CMAKE_SOURCE_DIR}/lib/lodepng.h ${CMAKE_SOURCE_DIR}/lib/lodepng.cpp)

add_library(lib ${LIB})

set(VECTOR_SOURCE
  Vector.hpp Vector.cpp)

set(SPHERE_SOURCE
  Sphere.hpp Sphere.cpp)

set(RAYTRACER_SOURCE
  RayTracer.hpp RayTracer.cpp)

set(RAYTRACER_MAIN
  RayTracer_main.cpp)
  
set(TEST_SOURCE
  RayTracer_tests.cpp)

set(SOURCE ${VECTOR_SOURCE} ${SPHERE_SOURCE} ${RAYTRACER_SOURCE})

# create unittests
add_executable(RayTracerMain ${SOURCE} ${RAYTRACER_MAIN})
add_executable(RayTracerTests catch.hpp ${SOURCE} ${TEST_SOURCE})
TARGET_LINK_LIBRARIES(RayTracerTests lib)
TARGET_LINK_LIBRARIES(RayTracerMain lib)