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

int main() {
    t_window w;
    t_scene scene;

    scene_init(&scene, 9);
    scene.camera = camera_init();
    init(&w);

    const t_vec3 pos[] = {
            {.6, .6, .6},
            {0, 1, 0}
    };

    const t_vec3 rect[] = {
            {-2, 0, -2},
            {4, 0, 0},
            {0, 0, 4},
            {0, 4, 0},
            {2, 0, 2},
            {0, 0, -4},
            {-4, 0, 0},
            {2, 4, 2},
            {-4, 0, 0},
            {0, 0, -4},
            {-1.5f, 3.99, -1.5f},
            {3, 0, 0},
            {0, 0, 3}
    };

    const t_vec3 box[] = {
            {-1, 0, -1},
            {0, 1, 0}
    };

    t_vec3 albedo[] = {
            {0, 1, 0},
            {1, 0, 0}
    };

    t_vec3 light[] = {
            {1, 1, 1}
    };

#define RED &albedo[0]
#define GREEN &albedo[1]

    scene.entities[8] = entity_create(PRIMITIVE_RECTANGLE, material_create(MATERIAL_EMITTER, &light[0]), NULL, rectangle_create(&rect[10], &rect[12], &rect[11]));
    vec3_assign(&scene.entities[8]->material->texture.emit_color, &light[0]);
    scene.entities[7] = entity_create(PRIMITIVE_AXIS_ALIGNED_BOX, material_create(MATERIAL_LAMBERTIAN, WHITE), NULL, box_create(&box[0], &box[1]));
    scene.entities[6] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_METAL, WHITE), &pos[0], sphere_create(.3f));
    scene.entities[5] = entity_create(PRIMITIVE_RECTANGLE, material_create(MATERIAL_LAMBERTIAN, WHITE), NULL, rectangle_create(&rect[7], &rect[8], &rect[9]));
    scene.entities[4] = entity_create(PRIMITIVE_RECTANGLE, material_create(MATERIAL_LAMBERTIAN, WHITE), NULL, rectangle_create(&rect[4], &rect[6], &rect[3]));
    scene.entities[3] = entity_create(PRIMITIVE_RECTANGLE, material_create(MATERIAL_LAMBERTIAN, GREEN), NULL, rectangle_create(&rect[4], &rect[3], &rect[5]));
    scene.entities[2] = entity_create(PRIMITIVE_RECTANGLE, material_create(MATERIAL_LAMBERTIAN, WHITE), NULL, rectangle_create(&rect[0], &rect[1], &rect[3]));
    scene.entities[1] = entity_create(PRIMITIVE_RECTANGLE, material_create(MATERIAL_LAMBERTIAN, RED), NULL, rectangle_create(&rect[0], &rect[3], &rect[2]));
    scene.entities[0] = entity_create(PRIMITIVE_RECTANGLE, material_create(MATERIAL_LAMBERTIAN, WHITE), NULL, rectangle_create(&rect[0], &rect[2], &rect[1]));

    //PPM HEADER
    while (SDL_PollEvent(&w.event))
        handle_events(w.event);
    thread_pool_render(&scene, &w, WIN_X, WIN_Y);
    while (1) {
        while (SDL_PollEvent(&w.event))
            handle_events(w.event);
        usleep(250);
        render(&w);
    }
    return (0);
}