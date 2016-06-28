//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "rt.h"
#include "libft/includes/libft.h"
#include "entity.h"

//static void get_sphere_uv(const t_vec3 *p, float *u, float *v)
//{
//    const float phi = atan2f(p->z, p->x);
//    const float theta = asinf(p->y);
//
//    *u = 1 - (phi + (float)M_PI) / (2 * (float)M_PI);
//    *v = (theta + (float)M_PI / 2) / (float)M_PI;
//}

t_bool      sphere_hit(t_entity *entity, const t_ray *r, t_precision precision, t_hit_record *hit)
{
    t_vec3  oc;
    float   a;
    float   b;
    float   c;
    float   delta;
    float   tmp;
    float   radius = ((t_primitive_sphere *)entity->data)->radius;

    vec3_sub(&oc, &RAY_ORIGIN(r), &entity->center);
    a = vec3_dot(&RAY_DIRECTION(r), &RAY_DIRECTION(r));
    b = vec3_dot(&oc, &RAY_DIRECTION(r));
    c = vec3_dot(&oc, &oc) - SQR(radius);
    delta = SQR(b) - a * c;
    if (delta > 0)
    {
        tmp = (-b - sqrtf(SQR(b) - a * c)) / a;
        if (tmp < precision.max && tmp > precision.min)
        {
            hit->t = tmp;
            ray_point_at(&hit->pos, r, hit->t);
            vec3_sub(&hit->normal, &hit->pos, &entity->center);
            vec3_div_f(&hit->normal, &hit->normal, radius);
            return (TRUE);
        }
        tmp = (-b + sqrtf(SQR(b) - a * c)) / a;
        if (tmp < precision.max && tmp > precision.min)
        {
            hit->t = tmp;
            ray_point_at(&hit->pos, r, hit->t);
            vec3_sub(&hit->normal, &hit->pos, &entity->center);
            vec3_div_f(&hit->normal, &hit->normal, radius);
            return (TRUE);
        }
    }
    return (FALSE);
}

t_bool      triangle_hit(t_entity *entity, const t_ray *r, t_precision precision, t_hit_record *hit)
{
    const float epsilon = 1e-8;
    t_primitive_triangle    *t;
    t_vec3 v0v1, v0v2, pvec, tvec, qvec;
    float delta, inv_delta;

    t = (t_primitive_triangle *)entity->data;
    vec3_sub(&v0v1, &t->v1, &t->v0);
    vec3_sub(&v0v2, &t->v2, &t->v0);
    vec3_cross(&pvec, &RAY_DIRECTION(r), &v0v2);
    delta = vec3_dot(&v0v1, &pvec);
//    UNCOMMENT FOR BACKFACE CULLING
//    if (delta < epsilon)
//        return (FALSE);
    if (fabsf(delta) < epsilon)
        return (FALSE);
    inv_delta = 1 / delta;
    vec3_sub(&tvec, &RAY_ORIGIN(r), &t->v0);
    hit->u = vec3_dot(&tvec, &pvec) * inv_delta;
    if (hit->u < precision.min || hit->u > 1)
        return (FALSE);
    vec3_cross(&qvec, &tvec, &v0v1);
    hit->v = vec3_dot(&RAY_DIRECTION(r), &qvec) * inv_delta;
    if (hit->v < precision.min || ((hit->v + hit-> u) > 1))
        return (FALSE);
    hit->t = vec3_dot(&v0v2, &qvec) * inv_delta;
    return (TRUE);
}
