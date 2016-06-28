//
// Created by Raphaël Dantzer on 28/06/16.
//

#include <pthread.h>
#include "rt.h"
#include "scene.h"
#include "libft/includes/libft.h"
#include "thread.h"

typedef struct          s_th_render
{
    int                 x;
    int                 y;
    int                 x_max;
    int                 y_max;
    t_scene             *scene;
    t_window            *w;
}                       t_th_render;

t_vec3 rt_color(const t_ray *r, t_scene *scene, int depth);

static t_vec3 retrace(const t_ray *r, t_scene *scene, int depth, t_vec3 *attenuation) {
    t_vec3 color;

    color = rt_color(r, scene, depth + 1);
    vec3_mul(&color, &color, attenuation);
    return (color);
}

t_vec3 rt_color(const t_ray *r, t_scene *scene, int depth) {
    t_hit_record record;
    t_precision precision;
    t_vec3 tmp, attenuation;
    t_ray sub_ray;
    const t_vec3 black = {0.f, 0.f, 0.f};

    precision.min = 0.001;
    precision.max = MAXFLOAT;
    if (scene_raytrace(scene, r, precision, &record)) {
        if (depth < 50 && record.material->scatter(record.material, r, &record, &attenuation, &sub_ray)) {
            return (retrace(&sub_ray, scene, depth, &attenuation));
        }
        else
            return (black);

    }
    else {
        t_vec3 u;
        float t;
        t_vec3 lerp;
        const t_vec3 gradient = {.5f, .7f, 1.f};

        vec3_unit_vector(&u, &RAY_DIRECTION(r));
        t = 0.5f * (u.y + 1.0f);
        vec3_add(&tmp, vec3_mul_f(&tmp, &g_vec3_identity, 1.0f - t), vec3_mul_f(&lerp, &gradient, t));
        return tmp;
    }
}

void    render_fragment(t_th_render *fragment)
{
    t_ray r;
    int nx = WIN_X;
    int ny = WIN_Y;
    int ns = WIN_NS;
    t_vec3 color;
    const t_vec3 lower_left_corner = {-2.0f, -1.0f, -1.0f};
    const t_vec3 horizontal = {4.0f, 0.0f, 0.0f};
    const t_vec3 vertical = {0.0f, 2.0f, 0.0f};
    const t_vec3 origin = {0.0f, 0.f, 0.0f};

    for (int j = fragment->y_max; j >= fragment->y; j--) {
        for (int i = fragment->x; i < fragment->x_max; i++) {
            ft_bzero(&color, sizeof(t_vec3));
            for (int s = 0; s < ns; s++) {
                float u = ((float) i + (float) drand48()) / (float) nx;
                float v = ((float) j + (float) drand48()) / (float) ny;
                t_vec3 v_pos;
                vec3_mul_f(&v_pos, &vertical, v);

                t_vec3 u_pos;
                vec3_mul_f(&u_pos, &horizontal, u);

                t_vec3 b;
                vec3_add(&b, &v_pos, &u_pos);

                t_vec3 tmp;
                camera_get_ray(&r, fragment->scene->camera, u, v);
//                ray_assign(&r, &origin, vec3_add(&tmp, &lower_left_corner, &b));
                t_vec3 tmp_color = rt_color(&r, fragment->scene, 0);
                vec3_add(&color, &color, &tmp_color);
            }
            vec3_div_f(&color, &color, (float) ns);
            t_rgb pixel;
            pixel.r = (int) (255.99 * color.x);
            pixel.g = (int) (255.99 * color.y);
            pixel.b = (int) (255.99 * color.z);
            draw_pixel(WIN_X - i, WIN_Y - j, pixel, &fragment->w->canvas);
        }
    }
}

void    *threaderize_render(void *th)
{
    t_th_render *fragment;

    fragment = (t_th_render *)th;
    render_fragment(fragment);
    return (NULL);
}

void    threaded_render(t_scene *scene, t_window *w, int width, int height)
{
    pthread_t tid[RT_THREADS];
    t_th_render th[RT_THREADS];
    int         sleeping;
    int         i, j;
    const int   step_x = width / RT_ROWS, step_y = height / RT_THREADS;

    sleeping = 0;
    i = -1;
    while (++i < RT_ROWS)
    {
        j = -1;
        while (++j < RT_THREADS)
        {
            th[j].scene = scene;
            th[j].x = i * step_x;
            th[j].x_max = (i + 1) * step_x;
            th[j].y = j * step_y;
            th[j].y_max = (j + 1) * step_y;
            th[j].w = w;
            pthread_create(&tid[j], NULL, threaderize_render, &th[j]);
        }
        j = -1;
        while (++j < RT_THREADS)
        {
            pthread_join(tid[j], NULL);
            render(w);
        }
    }
}