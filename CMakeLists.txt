cmake_minimum_required(VERSION 3.3)
project(Raytracer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

set(SOURCE_FILES *.c *.h)
include_directories(/usr/local/include/SDL2)