//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "m3d.h"

t_ray       *ray_assign(t_ray *r, const t_vec3 *a, const t_vec3 *b)
{
    vec3_assign(&r->a, a);
    vec3_assign(&r->b, b);
    return (r);
}

t_vec3      *ray_point_at(t_vec3 *v, const t_ray *r, float t)
{
    v = vec3_add(v, &r->a, vec3_mul_f(v, &r->b, t));
    return (v);
}