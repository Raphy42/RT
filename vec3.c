//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "m3d.h"
#include "libft/includes/libft.h"

const t_vec3 g_vec3_identity = {
        1.0f,
        1.0f,
        1.0f
};

t_vec3      *vec3_clear(t_vec3 *v) {
    ft_bzero(v, sizeof(t_vec3));
    return (v);
}

t_vec3      *vec3_assign(t_vec3 *v, const t_vec3 *src)
{
    ft_memcpy(v, src, sizeof(t_vec3));
    return (v);
}

t_vec3      *vec3_sub(t_vec3 *v, const t_vec3 *v1, const t_vec3 *v2)
{
    v->x = v1->x - v2->x;
    v->y = v1->y - v2->y;
    v->z = v1->z - v2->z;
    return (v);
}

t_vec3      *vec3_add(t_vec3 *v, const t_vec3 *v1, const t_vec3 *v2)
{
    v->x = v1->x + v2->x;
    v->y = v1->y + v2->y;
    v->z = v1->z + v2->z;
    return (v);
}

t_vec3      *vec3_div(t_vec3 *v, const t_vec3 *v1, const t_vec3 *v2)
{
    v->x = v1->x / v2->x;
    v->y = v1->y / v2->y;
    v->z = v1->z / v2->z;
    return (v);
}

t_vec3      *vec3_mul(t_vec3 *v, const t_vec3 *v1, const t_vec3 *v2)
{
    v->x = v1->x * v2->x;
    v->y = v1->y * v2->y;
    v->z = v1->z * v2->z;
    return (v);
}

t_vec3      *vec3_sub_f(t_vec3 *v, const t_vec3 *v1, float f)
{
    v->x = v1->x - f;
    v->y = v1->y - f;
    v->z = v1->z - f;
    return (v);
}

t_vec3      *vec3_add_f(t_vec3 *v, const t_vec3 *v1, float f)
{
    v->x = v1->x + f;
    v->y = v1->y + f;
    v->z = v1->z + f;
    return (v);
}

t_vec3      *vec3_div_f(t_vec3 *v, const t_vec3 *v1, float f)
{
    v->x = v1->x / f;
    v->y = v1->y / f;
    v->z = v1->z / f;
    return (v);
}

t_vec3      *vec3_mul_f(t_vec3 *v, const t_vec3 *v1, float f)
{
    v->x = v1->x * f;
    v->y = v1->y * f;
    v->z = v1->z * f;
    return (v);
}

float		vec3_dot(const t_vec3 *v1, const t_vec3 *v2)
{
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec3      *vec3_cross(t_vec3 *v, const t_vec3 *v1, const t_vec3 *v2)
{
    v->x = (v1->y * v2->z) - (v1->z * v2->y);
    v->y = (v1->z * v2->x) - (v1->x * v2->z);
    v->z = (v1->x * v2->y) - (v1->y * v2->x);
    return (v);
}

float       vec3_squared_length(const t_vec3 *v)
{
    return (SQR(v->x) + SQR(v->y) + SQR(v->z));
}

float       vec3_length(const t_vec3 *v)
{
    return (sqrtf(vec3_squared_length(v)));
}

/**
 * return src / src.length
 */
t_vec3      *vec3_unit_vector(t_vec3 *v, const t_vec3 *src)
{
    return (vec3_assign(v, vec3_div_f(v, src, vec3_length(src))));
}

t_vec3      *vec3_reflect(t_vec3 *v, const t_vec3 *v1, const t_vec3 *v2)
{
    t_vec3  tmp;

    vec3_mul_f(&tmp, v2, 2 * vec3_dot(v1, v2));
    return (vec3_sub(v, v1, &tmp));
}

t_vec3      *vec3_normalize(t_vec3 *v)
{
    float   length;

    length = vec3_length(v);
    v = vec3_div_f(v, v, length);
    return (v);
}
