cmake_minimum_required(VERSION 3.3)
project(Raytracer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

set(SOURCE_FILES main.c rt.h m3d.h main.c vec3.c ray.c)
add_executable(Raytracer ${SOURCE_FILES})
include_directories(minilibx_macos)