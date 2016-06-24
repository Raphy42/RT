//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "m3d.h"

t_vec3      *ray_point_at(t_vec3 *v, t_ray *r, float t)
{
    v = vec3_add(v, &r->a, vec3_mul_f(v, &r->b, t));
    return (v);
}