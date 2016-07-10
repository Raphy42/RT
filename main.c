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
#include "octree.h"

static void vec3_create(t_vec3 *v, float x, float y, float z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

int main() {
    t_window w;
    t_scene scene;
    t_octree *o;

    scene_init(&scene, 1000);
    scene.camera = camera_init();

    const t_vec3 origin = {0, 0, 0};
    const t_vec3 half_dimension = {10, 10, 10};

    o = octree_create(&origin, &half_dimension);

    int i = -1;
    for (int z = 0; z < 10; z++)
    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            t_vec3 a, b, color;
            t_octree_data *data = (t_octree_data *)ft_memalloc(sizeof(t_octree_data));
            color.x = sinf((float)x / 10.f);
            color.y = sinf((float)y / 10.f);
            color.z = sinf((float)z / 10.f);
            vec3_create(&a, x, y, z);
            vec3_create(&b, x + 0.5f, y + 0.5f, z + 0.5f);
            scene.entities[++i] = entity_create(PRIMITIVE_AXIS_ALIGNED_BOX, material_create(MATERIAL_DEBUG, &color), NULL, box_create(&a, &b));
            vec3_assign(&data->pos, &a);
            octree_insert(o, data);
        }
    }

    octree_destroy(o);
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