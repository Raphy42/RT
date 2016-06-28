//
// Created by Raphaël Dantzer on 27/06/16.
//

#include "rt.h"
#include "debug.h"

static void camera_build(t_camera *camera)
{
    float   theta;
    float   half_height;
    float   half_width;
    t_vec3  u, v, w;
    t_vec3  tmp;

    theta = camera->fov * (float)(M_PI / 180.f);
    half_height = tanf(theta / 2.f);
    half_width = camera->aspect * half_height;

    vec3_unit_vector(&w, vec3_sub(&tmp, &camera->eye, &camera->center));
    vec3_unit_vector(&u, vec3_cross(&tmp, &camera->p_up, &w));
    vec3_cross(&v, &w, &u);

    vec3_assign(&camera->lower_left_corner, &camera->eye);
    vec3_sub(&camera->lower_left_corner, &camera->lower_left_corner, vec3_mul_f(&tmp, &u, half_width));
    vec3_sub(&camera->lower_left_corner, &camera->lower_left_corner, vec3_mul_f(&tmp, &v, half_height));
    vec3_sub(&camera->lower_left_corner, &camera->lower_left_corner, &w);
    vec3_mul_f(&camera->horizontal, &u, 2 * half_width);
    vec3_mul_f(&camera->vertical, &v, 2 * half_height);
}

t_camera    *camera_init()
{
    t_camera    *camera;
    camera = (t_camera *)ft_memalloc(sizeof(t_camera));
    const t_vec3 eye = {2, 2, 3};
    const t_vec3 center = {0, 0, 0};
    const t_vec3 p_up = {0, 1, 0};
    camera->aspect = (float)(WIN_X) / (float)(WIN_Y);
    camera->fov = 90;
    vec3_assign(&camera->eye, &eye);
    vec3_assign(&camera->center, &center);
    vec3_assign(&camera->p_up, &p_up);
    camera_build(camera);
    return (camera);
}

void       camera_get_ray(t_ray *ray, t_camera *camera, float u, float v)
{
    t_vec3  s;
    t_vec3  t;

    vec3_mul_f(&s, &camera->horizontal, u);
    vec3_mul_f(&t, &camera->vertical, v);
    vec3_add(&s, &s, &t);
    vec3_sub(&s, &s, &camera->eye);
    vec3_add(&s, &camera->lower_left_corner, &s);
    ray_assign(ray, &camera->eye, &s);
}