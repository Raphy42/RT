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
    (void)attenuation;
    t_vec3 color;
    color = rt_color(r, scene, depth + 1);
    vec3_mul(&color, &color, attenuation);
    return (color);
}

static t_vec3   prepare_for_retrace(const t_ray *r, t_scene *scene, int depth, t_hit_record record)
{
    t_vec3      emit;
    t_vec3      attenuation;
    t_ray       sub_ray;
    t_vec3      tmp;

    ft_bzero(&emit, sizeof(t_vec3));
    if (record.material->type == MATERIAL_EMITTER)
        record.material->emit(record.material, &record, &emit);
    if (depth < 50 && record.material->scatter(record.material, r, &record, &attenuation, &sub_ray))
    {
        tmp = retrace(&sub_ray, scene, depth, &attenuation);
        vec3_add(&tmp, &emit, &tmp);
        return (tmp);
    }
    else
        return (emit);

}

t_vec3 rt_color(const t_ray *r, t_scene *scene, int depth) {
    t_hit_record    record;
    t_precision     precision;
    t_vec3          tmp;

    precision.min = 0.001;
    precision.max = MAXFLOAT;
    if (scene_raytrace(scene, r, precision, &record))
        return (prepare_for_retrace(r, scene, depth, record));
    else {
        t_vec3 u;
        float t;
        t_vec3 lerp;
        const t_vec3 gradient = {.5f, .7f, 1.f};

        vec3_unit_vector(&u, &RAY_DIRECTION(r));
        t = 0.5f * (u.y + 1.0f);
        vec3_add(&tmp, vec3_mul_f(&tmp, &g_vec3_identity, 1.0f - t), vec3_mul_f(&lerp, &gradient, t));
//        const t_vec3 black = {0.f, 0.f, 0.f};
//        return (black);
        return (tmp);
    }
}

void    render_fragment(t_th_render *fragment)
{
    t_ray r;
    int nx = WIN_X;
    int ny = WIN_Y;
    int ns = WIN_NS;
    t_vec3 color;

    for (int j = fragment->y_max; j >= fragment->y; j--) {
        for (int i = fragment->x; i < fragment->x_max; i++) {
            ft_bzero(&color, sizeof(t_vec3));
            for (int s = 0; s < ns; s++) {
                float u = ((float) i + (float)drand48()) / (float)nx;
                float v = ((float) j + (float)drand48()) / (float)ny;
                camera_get_ray(&r, fragment->scene->camera, u, v);
                t_vec3 tmp_color = rt_color(&r, fragment->scene, 0);
                vec3_add(&color, &color, &tmp_color);
            }
            vec3_div_f(&color, &color, (float)ns);
            t_rgb pixel;
            pixel.r = (int)(255.99 * clamp(color.x, 0, 1));
            pixel.g = (int)(255.99 * clamp(color.y, 0, 1));
            pixel.b = (int)(255.99 * clamp(color.z, 0, 1));
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