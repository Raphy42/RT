//
// Created by Raphaël Dantzer on 27/06/16.
//

#include "rt.h"

t_vec3 random_in_unit_sphere()
{
    t_vec3 p;
    t_vec3 tmp;

    tmp.x = (float) drand48();
    tmp.y = (float) drand48();
    tmp.z = (float) drand48();
    vec3_sub(&p, vec3_mul_f(&p, &tmp, 2.0), &g_vec3_identity);
    while (vec3_squared_length(&p) >= 1.0) {
        tmp.x = (float) drand48();
        tmp.y = (float) drand48();
        tmp.z = (float) drand48();
        vec3_sub(&p, vec3_mul_f(&p, &tmp, 2.0), &g_vec3_identity);
    }
    return (p);
}

t_bool           lambertian(t_material *material, const t_ray *r, const t_hit_record *h, t_vec3 *attenuation, t_ray *scattered)
{
    (void)r;
    t_vec3      target;
    t_vec3      random;

    random = random_in_unit_sphere();
    vec3_add(&target, vec3_add(&target, &h->normal, &h->pos), &random);
    ray_assign(scattered, &h->pos, vec3_sub(&target, &target, &h->pos));
    vec3_assign(attenuation, &material->albedo);
    return (TRUE);
}

t_bool           metal(t_material *material, const t_ray *r, const t_hit_record *h, t_vec3 *attenuation, t_ray *scattered)
{
    t_vec3      reflected;

    vec3_reflect(&reflected, vec3_unit_vector(&reflected, &RAY_DIRECTION(r)), &h->normal);
    ray_assign(scattered, &h->pos, &reflected);
    vec3_assign(attenuation, &material->albedo);
    return (vec3_dot(&RAY_DIRECTION(scattered), &h->normal) > 0);
}
