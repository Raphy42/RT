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
#include "entity.h"

int main() {
    t_window w;
    t_scene scene;

    t_vec3 albedo[] = {{.8f, .3f, .3f},
                       {.4f, .4f, .4f},
                       {.8f, .6f, .2f},
                       {1.f, 1.f, 1.f}};
    scene_init(&scene, 9);
    scene.camera = camera_init();
    const t_vec3 pos[] = {{0,     0,      1.5},
                          {0,     0,      -1.5f},
                          {-1.5f, 0,      0},
                          {1.5f,  0,      0},
                          {0,     0.5,    3},
                          {0,     0.5f,   -3.f},
                          {-3.f,  0.5f,   0},
                          {3.f,   0.5,    0},
                          {0.f,   -105.f, 0.f},
                          {1.f,   1.f,    1.f}
    };

    const t_vec3 vertices[] = {
            {-1.0f, -1.0f, -1.0f},
            {-1.0f, -1.0f, 1.0f},
            {-1.0f, 1.0f,  1.0f},
            {1.0f,  1.0f,  -1.0f},
            {-1.0f, -1.0f, -1.0f},
            {-1.0f, 1.0f,  -1.0f},
            {1.0f,  -1.0f, 1.0f},
            {-1.0f, -1.0f, -1.0f},
            {1.0f,  -1.0f, -1.0f},
            {1.0f,  1.0f,  -1.0f},
            {1.0f,  -1.0f, -1.0f},
            {-1.0f, -1.0f, -1.0f},
            {-1.0f, -1.0f, -1.0f},
            {-1.0f, 1.0f,  1.0f},
            {-1.0f, 1.0f,  -1.0f},
            {1.0f,  -1.0f, 1.0f},
            {-1.0f, -1.0f, 1.0f},
            {-1.0f, -1.0f, -1.0f},
            {-1.0f, 1.0f,  1.0f},
            {-1.0f, -1.0f, 1.0f},
            {1.0f,  -1.0f, 1.0f},
            {1.0f,  1.0f,  1.0f},
            {1.0f,  -1.0f, -1.0f},
            {1.0f,  1.0f,  -1.0f},
            {1.0f,  -1.0f, -1.0f},
            {1.0f,  1.0f,  1.0f},
            {1.0f,  -1.0f, 1.0f},
            {1.0f,  1.0f,  1.0f},
            {1.0f,  1.0f,  -1.0f},
            {-1.0f, 1.0f,  -1.0f},
            {1.0f,  1.0f,  1.0f},
            {-1.0f, 1.0f,  -1.0f},
            {-1.0f, 1.0f,  1.0f},
            {1.0f,  1.0f,  1.0f},
            {-1.0f, 1.0f,  1.0f},
            {1.0f,  -1.0f, 1.0f},
    };

    t_material *checkboard = material_create(MATERIAL_DEBUG, &albedo[0]);
    checkboard->texture.value = &checker;
    scene.entities[0] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DIELECTRIC, &albedo[3]), &pos[0], sphere_create(1));
    scene.entities[1] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DIELECTRIC, &albedo[3]), &pos[1], sphere_create(1));
    scene.entities[2] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DIELECTRIC, &albedo[3]), &pos[2], sphere_create(1));
    scene.entities[3] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DIELECTRIC, &albedo[3]), &pos[3], sphere_create(1));
    scene.entities[4] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[4], sphere_create(1.5f));
    scene.entities[5] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[5], sphere_create(1.5f));
    scene.entities[6] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[6], sphere_create(1.5f));
    scene.entities[7] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[7], sphere_create(1.5f));
    scene.entities[8] = entity_create(PRIMITIVE_SPHERE, checkboard, &pos[8], sphere_create(100.f));
//    scene.entities[0]  = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[0], &vertices[1], &vertices[2]));
//    scene.entities[1]  = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[3], &vertices[4], &vertices[5]));
//    scene.entities[2]  = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[6], &vertices[7], &vertices[8]));
//    scene.entities[3]  = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[9], &vertices[10], &vertices[12]));
//    scene.entities[4]  = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[12], &vertices[13], &vertices[14]));
//    scene.entities[5]  = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[15], &vertices[16], &vertices[17]));
//    scene.entities[6]  = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[18], &vertices[19], &vertices[20]));
//    scene.entities[7]  = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[21], &vertices[22], &vertices[23]));
//    scene.entities[8]  = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[24], &vertices[25], &vertices[26]));
//    scene.entities[9]  = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[27], &vertices[28], &vertices[29]));
//    scene.entities[10] = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[30], &vertices[31], &vertices[32]));
//    scene.entities[11] = entity_create(PRIMITIVE_TRIANGLE, material_create(MATERIAL_DEBUG, &albedo[3]), &pos[8], triangle_create(&vertices[33], &vertices[34], &vertices[35]));


    init(&w);
    //PPM HEADER
    while (SDL_PollEvent(&w.event))
        handle_events(w.event);
    threaded_render(&scene, &w, WIN_X, WIN_Y);
    while (1) {
        while (SDL_PollEvent(&w.event))
            handle_events(w.event);
        render(&w);
    }
    return (0);
}