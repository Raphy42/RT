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

int main() {
    t_window w;
    t_scene scene;
    t_vec3 color;
    t_camera camera;

    scene_init(&scene, 4);
    const t_vec3 pos[] = {{0, 0,       -1},
                          {0, -100.5f, -1.f},
                          {1, 0, -1},
                          {-1, 0, -1}};
    t_vec3 albedo[] = {{.8f, .3f, .3f},
                       {.8f, .8f, .0f},
                       {.8f, .6f, .2f},
                       {.8f, .8f, .8f}};
    scene.entities[0] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_LAMBERTIAN, &albedo[0]), &pos[0], 0.5);
    scene.entities[1] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_LAMBERTIAN, &albedo[1]), &pos[1], 100);
    scene.entities[2] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_METAL, &albedo[2]), &pos[2], 0.5);
    scene.entities[3] = entity_create(PRIMITIVE_SPHERE, material_create(MATERIAL_METAL, &albedo[3]), &pos[3], 0.5);

    int nx = WIN_X;
    int ny = WIN_Y;
    int ns = WIN_NS;
    const t_vec3 lower_left_corner = {-2.0f, -1.0f, -1.0f};
    const t_vec3 horizontal = {4.0f, 0.0f, 0.0f};
    const t_vec3 vertical = {0.0f, 2.0f, 0.0f};
    const t_vec3 origin = {0.0f, 0.f, 0.0f};
    const t_vec3 p_up = {0.f, -1.f, 0.f};
    const t_vec3 eye = {-2.f, 2.f, 1.f};

    vec3_assign(&camera.eye, &eye);
    vec3_assign(&camera.p_up, &p_up);
    vec3_assign(&camera.center, &origin);
    camera.fov = 90;
    camera.aspect = (float) nx / (float) ny;

    camera_init(&camera);
    t_ray r;
    init(&w);
    //PPM HEADER
    for (int j = ny; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            ft_bzero(&color, sizeof(t_vec3));
            for (int s = 0; s < ns; s++) {
                float u = ((float) i + (float) drand48()) / (float) nx;
                float v = ((float) j + (float) drand48()) / (float) ny;
//
                t_vec3 v_pos;
                vec3_mul_f(&v_pos, &vertical, v);

                t_vec3 u_pos;
                vec3_mul_f(&u_pos, &horizontal, u);

                t_vec3 b;
                vec3_add(&b, &v_pos, &u_pos);

                t_vec3 tmp;
                ray_assign(&r, &origin, vec3_add(&tmp, &lower_left_corner, &b));
//            r = camera_get_ray(&camera, u, v);

                t_vec3 tmp_color = rt_color(&r, &scene, 0);
                vec3_add(&color, &color, &tmp_color);
            }
            vec3_div_f(&color, &color, (float) ns);
            t_rgb pixel;
            pixel.r = (int) (255.99 * color.x);
            pixel.g = (int) (255.99 * color.y);
            pixel.b = (int) (255.99 * color.z);
            draw_pixel(WIN_X - i, WIN_Y - j, pixel, &w.canvas);
        }
    }
    while (1) {
        while (SDL_PollEvent(&w.event))
            handle_events(w.event);
        render(&w);
    }
    return (0);
}