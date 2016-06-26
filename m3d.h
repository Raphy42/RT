//
// Created by Raphaël Dantzer on 24/06/16.
//

#ifndef RAYTRACER_3D_MATH_H
#define RAYTRACER_3D_MATH_H

#include <math.h>
#include <stdint.h>

#define SQR(x) (x * x)

typedef struct s_vec3 {
    float x;
    float y;
    float z;
} t_vec3;

extern const t_vec3 g_vec3_identity;

typedef struct s_mat4 {
    float m[16];
} t_mat4;

#define RAY_ORIGIN(r) (r->a)
#define RAY_DIRECTION(r) (r->b)

typedef struct s_ray {
    t_vec3  a;
    t_vec3  b;
} t_ray;

typedef struct s_rgb
{
    int r;
    int g;
    int b;
} t_rgb;

/**
 * VEC3.c
 */
t_vec3      *vec3_clear(t_vec3 *v);
t_vec3      *vec3_assign(t_vec3 *v, const t_vec3 *src);

t_vec3      *vec3_sub(t_vec3 *v, const t_vec3 *v1, const t_vec3 *v2);
t_vec3      *vec3_add(t_vec3 *v, const t_vec3 *v1, const t_vec3 *v2);
t_vec3      *vec3_div(t_vec3 *v, const t_vec3 *v1, const t_vec3 *v2);
t_vec3      *vec3_mul(t_vec3 *v, const t_vec3 *v1, const t_vec3 *v2);

t_vec3      *vec3_sub_f(t_vec3 *v, const t_vec3 *v1, float f);
t_vec3      *vec3_add_f(t_vec3 *v, const t_vec3 *v1, float f);
t_vec3      *vec3_div_f(t_vec3 *v, const t_vec3 *v1, float f);
t_vec3      *vec3_mul_f(t_vec3 *v, const t_vec3 *v1, float f);

float       vec3_dot(const t_vec3 *v1, const t_vec3 *v2);
t_vec3      *vec3_cross(t_vec3 *v, const t_vec3 *v1, const t_vec3 *v2);
float       vec3_squared_length(const t_vec3 *v);
float       vec3_length(const t_vec3 *v);

t_vec3      *vec3_unit_vector(t_vec3 *v, const t_vec3 *src);

/**
 * RAY.c
 */
t_ray       *ray_assign(t_ray *r, const t_vec3 *a, const t_vec3 *b);
t_vec3      *ray_point_at(t_vec3 *v, const t_ray *r, float t);

#endif //RAYTRACER_3D_MATH_H
