//
// Created by Raphaël Dantzer on 27/06/16.
//

#include "rt.h"

void        camera_init(t_camera *camera)
{
    float   theta;
    float   half_height;
    float   half_width;
    t_vec3  u, v, w;
    t_vec3  tmp;

    theta = camera->fov * (float)(M_PI / 180);
    half_height = tanf(theta / 2);
    half_width = camera->aspect * half_height;

    vec3_unit_vector(&w, vec3_sub(&tmp, &camera->eye, &camera->center));
    vec3_unit_vector(&u, vec3_cross(&tmp, &camera->p_up, &w));
    vec3_cross(&v, &w, &u);
    camera->lower_left_corner.x = -half_width;
    camera->lower_left_corner.y = -half_width;
    camera->lower_left_corner.z = 1.0f;
    vec3_mul_f(&camera->horizontal, &u, 2 * half_width);
    vec3_mul_f(&camera->vertical, &v, 2 * half_height);
}

t_ray       camera_get_ray(t_camera *camera, float u, float v)
{
    t_ray   ray;
    t_vec3  s;
    t_vec3  t;

    vec3_mul_f(&s, &camera->horizontal, u);
    vec3_mul_f(&t, &camera->vertical, v);
    vec3_add(&s, &s, &t);
    vec3_sub(&s, &s, &camera->eye);
    vec3_add(&s, &camera->lower_left_corner, &s);
    ray_assign(&ray, &camera->eye, &s);
    return (ray);
}