cmake_minimum_required(VERSION 3.3)
project(Raytracer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -O2 -D_THREAD_SAFE")
set(SOURCE_FILES camera.c
        debug.c
        draw.c
        entity.c
        events.c
        init.c
        light.c
        main.c
        materials.c
        octree.c
        ray.c
        raytrace.c
        safe_alloc.c
        scene.c
        texture.c
        render.c
        utils.c
        vec3.c
        aabb.c
        thread_pool.c thread_pool.h job.c semaphore.c)

add_library(sdl2 STATIC IMPORTED)
set_target_properties(sdl2 PROPERTIES IMPORTED_LOCATION /usr/local/lib/libSDL2.a)
add_executable(Raytracer ${SOURCE_FILES})
include_directories(/usr/local/include/SDL2)
target_link_libraries(Raytracer ${CMAKE_SOURCE_DIR}/libft/libft.a sdl2)