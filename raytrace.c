//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "rt.h"
#include "libft/includes/libft.h"

static void get_sphere_uv(const t_vec3 *p, float *u, float *v)
{
    const float phi = atan2f(p->z, p->x);
    const float theta = asinf(p->y);

    *u = 1 - (phi + (float)M_PI) / (2 * (float)M_PI);
    *v = (theta + (float)M_PI / 2) / (float)M_PI;
}


t_bool      sphere_hit(t_entity *entity, const t_ray *r, t_precision precision, t_hit_record *hit)
{
    t_vec3  oc;
    float   a;
    float   b;
    float   c;
    float   delta;
    float   tmp;

    vec3_sub(&oc, &RAY_ORIGIN(r), &entity->center);
    a = vec3_dot(&RAY_DIRECTION(r), &RAY_DIRECTION(r));
    b = vec3_dot(&oc, &RAY_DIRECTION(r));
    c = vec3_dot(&oc, &oc) - SQR(entity->radius);
    delta = SQR(b) - a * c;
    if (delta > 0)
    {
        tmp = (-b - sqrtf(SQR(b) - a * c)) / a;
        if (tmp < precision.max && tmp > precision.min)
        {
            hit->t = tmp;
            ray_point_at(&hit->pos, r, hit->t);
            vec3_sub(&hit->normal, &hit->pos, &entity->center);
            vec3_div_f(&hit->normal, &hit->normal, entity->radius);
            return (TRUE);
        }
        tmp = (-b + sqrtf(SQR(b) - a * c)) / a;
        if (tmp < precision.max && tmp > precision.min)
        {
            hit->t = tmp;
            ray_point_at(&hit->pos, r, hit->t);
            vec3_sub(&hit->normal, &hit->pos, &entity->center);
            vec3_div_f(&hit->normal, &hit->normal, entity->radius);
            return (TRUE);
        }
    }
    return (FALSE);
}

