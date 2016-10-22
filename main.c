//
// Created by Raphaël Dantzer on 24/06/16.
//

#include <time.h>
#include <pthread.h>
#include "m3d.h"
#include "debug.h"
#include "rt.h"
#include "scene.h"
#include "entity.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WHITE (t_vec3 *)&g_vec3_identity
void sighandler(int signal)
{
    (void)signal;
    exit(EXIT_FAILURE);
}

int main() {
    signal(SIGINT, &sighandler);
    t_window w;
    t_scene scene;

    scene_init(&scene, 1004);
    scene.camera = camera_init();
    const t_vec3 pos[] = {
            {0, -5, 10},
            {0, -5, 10},
            {10, -5, 0},
            {10, -5, 10}
    };

    int i = -1;
    for (int z = 0; z < 10; z++)
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                t_vec3 a, b, color;
                color.x = sinf((float) x / 10.f);
                color.y = sinf((float) y / 10.f);
                color.z = sinf((float) z / 10.f);
                a.x =x; a.y = y; a.z = z;
                b.x = x + 0.5f;b.y =  y + 0.5f;b.z = z + 0.5f;
                if (y % 2 && x % 2 && z % 2) {
                    scene.entities[++i] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_METAL, (t_vec3 *)&g_vec3_identity), &a,
                                                        sphere_create(0.5f));
                }
                else
                {
                    scene.entities[++i] = entity_create(PRIMITIVE_AXIS_ALIGNED_BOX,
                                                        material_create(MATERIAL_LAMBERTIAN, &color), NULL,
                                                        box_create(&a, &b));
                }
            }
        }
    scene.entities[1000] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_METAL, (t_vec3 *)&g_vec3_identity), &pos[0], sphere_create(7.f));
    scene.entities[1001] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_METAL, (t_vec3 *)&g_vec3_identity), &pos[1], sphere_create(7.f));
    scene.entities[1002] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_METAL, (t_vec3 *)&g_vec3_identity), &pos[2], sphere_create(7.f));
    scene.entities[1003] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_METAL, (t_vec3 *)&g_vec3_identity), &pos[3], sphere_create(7.f));
    init(&w);
    //PPM HEADER
    while (SDL_PollEvent(&w.event))
        handle_events(w.event);
    thread_pool_render(&scene, &w, WIN_X, WIN_Y);
    while (1) {
        while (SDL_PollEvent(&w.event))
            handle_events(w.event);
        sleep(1);
        render(&w);
    }
    return (0);
}

