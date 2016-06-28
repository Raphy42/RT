//
// Created by Raphaël Dantzer on 24/06/16.
//

#include <time.h>
#include "m3d.h"
#include "debug.h"
#include "libft/includes/libft.h"
#include "rt.h"
#include "safe_alloc.h"
#include "scene.h"

int main() {
    t_window w;
    t_scene scene;

    t_vec3 albedo[] = {{.8f, .3f, .3f},
                       {.4f, .4f, .4f},
                       {.8f, .6f, .2f},
                       {1.f, 1.f, 1.f}};
    scene_init(&scene, 8);
    scene.camera = camera_init();
    const t_vec3 pos[] = {{0,     0, 1.5},
                          {0,     0, -1.5f},
                          {-1.5f, 0, 0},
                          {1.5f,  0, 0},
                          {0, 0.5, 3},
                          {0, 0.5f, -3.f},
                          {-3.f, 0.5f, 0},
                          {3.f, 0.5, 0}};

    scene.entities[0] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[0]), &pos[0], 1);
    scene.entities[1] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[0]), &pos[1], 1);
    scene.entities[2] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[2], 1);
    scene.entities[3] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[3], 1);
    scene.entities[4] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[0]), &pos[4], 1.5f);
    scene.entities[5] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[0]), &pos[5], 1.5f);
    scene.entities[6] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[6], 1.5f);
    scene.entities[7] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[7], 1.5f);
    init(&w);
    //PPM HEADER
    threaded_render(&scene, &w, WIN_X, WIN_Y);
    while (1) {
        while (SDL_PollEvent(&w.event))
            handle_events(w.event);
        render(&w);
    }
    return (0);
}