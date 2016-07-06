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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
    t_window w;
    t_scene scene;

    t_vec3 albedo[] = {{.8f, .3f, .3f},
                       {.4f, .4f, .4f},
                       {.8f, .6f, .2f},
                       {1.f, 1.f, 1.f}};
    scene_init(&scene, 11);
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
                          {1.f,   1.f,    1.f},
                          {4,     4,      0},
                          {12, -12, 0},
                          {-12, -12, 0}
    };

    const t_vec3 rectangle[] = {
            {-5, 0, -5},
            {10, 0, 0},
            {0, 0, 10}
    };

    const t_vec3 box_bound[] = {
            {2, 2, 2},
            {3, 3, 3}
    };

    t_vec3 light = {10.0, 10.0, 10.0};

    t_material *checkboard = material_create(MATERIAL_DEBUG, &albedo[3]);
    checkboard->texture.value = &checker;

    t_material  *image_test = material_create(MATERIAL_LAMBERTIAN, &albedo[3]);
    image_test->texture.image = (t_image *)ft_memalloc(sizeof(t_image));
    image_test->texture.image->data = stbi_load("grmy.PNG", &image_test->texture.image->w, &image_test->texture.image->h, &image_test->texture.image->n, 0);
    image_test->texture.value = texture_map;

    scene.entities[9] = entity_create(PRIMITIVE_AXIS_ALIGNED_BOX, checkboard, NULL, box_create(&box_bound[0], &box_bound[1]));
    scene.entities[10] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_METAL, &albedo[3]), &pos[0], sphere_create(1));
    scene.entities[1] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_METAL, &albedo[3]), &pos[1], sphere_create(1));
    scene.entities[2] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_LAMBERTIAN, &albedo[3]), &pos[2], sphere_create(1));
    scene.entities[3] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_LAMBERTIAN, &albedo[3]), &pos[3], sphere_create(1));
    scene.entities[4] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_METAL, &albedo[1]), &pos[4], sphere_create(1.5f));
    scene.entities[5] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_LAMBERTIAN, &albedo[2]), &pos[5], sphere_create(1.5f));
    scene.entities[6] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_LAMBERTIAN, &albedo[3]), &pos[6], sphere_create(1.5f));
    scene.entities[7] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_DIELECTRIC, &albedo[0]), &pos[7], sphere_create(1.5f));
    scene.entities[8] = entity_create(PRIMITIVE_SPHERE, checkboard, &pos[8], sphere_create(100.f));
    scene.entities[0] = entity_create(PRIMITIVE_RECTANGLE, image_test, &pos[10], rectangle_create(&rectangle[0], &rectangle[1], &rectangle[2]));

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