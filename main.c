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

t_vec3 random_in_unit_sphere()
{
    t_vec3  p;
    t_vec3  tmp;

    tmp.x = (float)drand48();
    tmp.y = (float)drand48();
    tmp.z = (float)drand48();
    while (vec3_squared_length(&p) >= 1.0)
    {
        tmp.x = (float)drand48();
        tmp.y = (float)drand48();
        tmp.z = (float)drand48();
        vec3_sub(&p, vec3_mul_f(&p, &tmp, 2.0), &g_vec3_identity);
    }
    return (p);
}

t_vec3 rt_color(const t_ray *r, t_scene *scene)
{
    t_hit_record    record;
    t_precision     precision;
    t_vec3 tmp, target, color, random;

    precision.min = 0.001;
    precision.max = MAXFLOAT;
    if (scene_raytrace(scene, r, precision, &record))
    {
        random = random_in_unit_sphere();
        vec3_add(&target, vec3_add(&tmp, &record.normal, &record.pos), &random);
        t_ray sub_ray;

        ray_assign(&sub_ray, &record.pos, vec3_sub(&tmp, &target, &record.pos));
        color = rt_color(&sub_ray, scene);
        vec3_mul_f(&color, &color, 0.5);
        return (color);
    }
    else {
        t_vec3 uv;
        t_vec3  v;
        const t_vec3 gradient = {0.5f, 0.7f, 1.0f};
        float   t;

        vec3_unit_vector(&uv, &RAY_DIRECTION(r));
        t = 0.5f * (uv.y + 1.0f);
        // fprintf(stderr, "%f\n", t);
        t_vec3 lerp;
        vec3_mul_f(&lerp, &g_vec3_identity, (1.0f - t));

        t_vec3 colorbase;
        vec3_mul_f(&color, &gradient, t);

        vec3_add(&v, &lerp, &colorbase);
        return (v);
    }
}

int main()
{
    t_window w;
    t_scene scene;
    t_vec3 color;

    scene_init(&scene, 2);
    const t_vec3 pos[] = {{0, 0, -1}, {0, 100.5f, -1.f}, {0, -1, -1}};
    scene.entities[0] = entity_create(PRIMITIVE_SPHERE, &pos[0], 0.5);
    scene.entities[1] = entity_create(PRIMITIVE_SPHERE, &pos[1], 100);

    int nx = WIN_X, ny = WIN_Y, ns = 100;
    const t_vec3 lower_left_corner = {-2.0f, -1.0f, -1.0f};
    const t_vec3 horizontal = {4.0f, 0.0f, 0.0f};
    const t_vec3 vertical = {0.0f, 2.0f, 0.0f};
    const t_vec3 origin = {0.0f, 0.0f, 0.0f};

    t_ray r;
    init(&w);
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            ft_bzero(&color, sizeof(t_vec3));
            for (int s = 0; s < ns; s++) {
                float u = ((float)i + (float)drand48()) / (float)nx;
                float v = ((float)j + (float)drand48()) / (float)ny;

                t_vec3 v_pos;
                vec3_mul_f(&v_pos, &vertical, v);

                t_vec3 u_pos;
                vec3_mul_f(&u_pos, &horizontal, u);

                t_vec3 b;
                vec3_add(&b, &v_pos, &u_pos);

                t_vec3 tmp;
                ray_assign(&r, &origin, vec3_add(&tmp, &lower_left_corner, &b));

                t_vec3 color_tmp = rt_color(&r, &scene);
                vec3_add(&color, &color, &color_tmp);
            }
            vec3_div_f(&color, &color, (float)ns);
            t_rgb pixel;
            pixel.r = (int)(255.99 * color.x);
            pixel.g = (int)(255.99 * color.y);
            pixel.b = (int)(255.99 * color.z);
            draw_pixel(i, j, pixel, &w.canvas);
        }
        ft_putnbr(j); ft_putchar('\n');
    }
    while (1)
    {
        while (SDL_PollEvent(&w.event))
            handle_events(w.event);
        render(&w);
    }
    return (0);
}