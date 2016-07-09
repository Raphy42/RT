cmake_minimum_required(VERSION 3.3)
project(Raytracer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

set(SOURCE_FILES main.c rt.h m3d.h main.c vec3.c ray.c debug.c debug.h init.c draw.c events.c raytrace.c scene.c entity.c safe_alloc.c safe_alloc.h scene.h camera.c materials.c thread.c thread.h pipeline.h texture.c entity.h obj.h light.c utils.c stb_image.h bvh/bvh.h aabb.c)
add_executable(Raytracer ${SOURCE_FILES})
include_directories(/usr/local/include/SDL2)