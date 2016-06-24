//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "m3d.h"
#include "debug.h"
#include "libft/includes/libft.h"
#include "rt.h"
#include "safe_alloc.h"
#include "scene.h"

float hit_sphere(const t_vec3 *center, float radius, const t_ray *r)
{
    t_vec3      oc;

    vec3_sub(&oc, &RAY_ORIGIN(r), center);
    float a = vec3_dot(&RAY_DIRECTION(r), &RAY_DIRECTION(r));
    float b = 2.0f * vec3_dot(&oc, &RAY_DIRECTION(r));
    float c = vec3_dot(&oc, &oc) - SQR(radius);
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1.0f);
    else
        return ((-b - sqrtf(discriminant)) / (2.0f * a));
}

t_vec3 rt_color(const t_ray *r)
{
    t_vec3 uv;
    t_vec3  v;
    const t_vec3 gradient = {0.5f, 0.7f, 1.0f};
    float   t;
    t_vec3 center = {0.0f, 0.0f, -1.0f};

    t = hit_sphere(&center, 0.5f, r);
    if (t > 0.0)
    {
        t_vec3 tmp;
        const t_vec3 haha = {0.f, 0.f, -1.f};
        vec3_mul_f(&tmp, vec3_add_f(&tmp, vec3_unit_vector(&tmp, vec3_sub(&tmp, ray_point_at(&tmp, r, t), &haha)), 1.0f), .5f);
        return tmp;
    }

    vec3_unit_vector(&uv, &RAY_DIRECTION(r));
    t = 0.5f * (uv.y + 1.0f);
   // fprintf(stderr, "%f\n", t);
    t_vec3 lerp;
    vec3_mul_f(&lerp, &g_vec3_identity, (1.0f - t));

    t_vec3 color;
    vec3_mul_f(&color, &gradient, t);

    vec3_add(&v, &lerp, &color);
    return (v);
}

int main()
{
    t_window w;
    t_scene s;

    scene_init(&s, 2);
    const t_vec3 pos[2] = {{0, 0, -1}, {0, -100.5f, -1.f}};
    s.entities[0] = entity_create(PRIMITIVE_SPHERE, &pos[0], 0.5);
    s.entities[0] = entity_create(PRIMITIVE_SPHERE, &pos[1], 100);


    int nx = WIN_X, ny = WIN_Y;
    const t_vec3 lower_left_corner = {-2.0f, -1.0f, -1.0f};
    const t_vec3 horizontal = {4.0f, 0.0f, 0.0f};
    const t_vec3 vertical = {0.0f, 2.0f, 0.0f};
    const t_vec3 origin = {0.0f, 0.0f, 0.0f};

    t_ray r;
    init(&w);
    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            float u = (float)i / (float)nx;
            float v = (float)j / (float)ny;

            t_vec3 v_pos;
            vec3_mul_f(&v_pos, &vertical, v);

            t_vec3 u_pos;
            vec3_mul_f(&u_pos, &horizontal, u);

            t_vec3 b;
            vec3_add(&b, &v_pos, &u_pos);

            t_vec3 tmp;
            ray_assign(&r, &origin, vec3_add(&tmp, &lower_left_corner, &b));

            t_vec3 color = rt_color(&r);
            t_rgb pixel;
            pixel.r = (int)(255.99 * color.x);
            pixel.g = (int)(255.99 * color.y);
            pixel.b = (int)(255.99 * color.z);
            draw_pixel(i, j, pixel, &w.canvas);
        }
    }
    while (1)
    {
        while (SDL_PollEvent(&w.event))
            handle_events(w.event);
        render(&w);
    }
    return (0);
}