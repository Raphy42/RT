//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "rt.h"
#include "libft/includes/libft.h"
#include "entity.h"
#include "debug.h"

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
            vec3_sub(&oc, &hit->pos, &entity->center);
            get_sphere_uv(vec3_div_f(&oc, &oc, radius), &hit->u, &hit->v);
            return (TRUE);
        }
        tmp = (-b + sqrtf(SQR(b) - a * c)) / a;
        if (tmp < precision.max && tmp > precision.min)
        {
            hit->t = tmp;
            ray_point_at(&hit->pos, r, hit->t);
            vec3_sub(&hit->normal, &hit->pos, &entity->center);
            vec3_div_f(&hit->normal, &hit->normal, radius);
            vec3_sub(&oc, &hit->pos, &entity->center);
            get_sphere_uv(vec3_div_f(&oc, &oc, radius), &hit->u, &hit->v);
            return (TRUE);
        }
    }
    return (FALSE);
}

//TODO REFACTOR
t_bool      triangle_hit(t_entity *entity, const t_ray *r, t_precision precision, t_hit_record *hit)
{
    (void)precision;
    const float epsilon = 1e-8;
    const t_vec3 normal = {0, 0, 1};
    t_primitive_triangle    *triangle;
    t_vec3 v0v1, v0v2, pvec, tvec, qvec;
    float delta, inv_delta;

    triangle = (t_primitive_triangle *)entity->data;
    vec3_sub(&v0v1, &triangle->v1, &triangle->v0);
    vec3_sub(&v0v2, &triangle->v2, &triangle->v0);
    vec3_cross(&pvec, &RAY_DIRECTION(r), &v0v2);
    delta = vec3_dot(&v0v1, &pvec);
//    UNCOMMENT FOR BACKFACE CULLING
//    if (delta < epsilon)
//        return (FALSE);
    if (fabsf(delta) < epsilon)
        return (FALSE);
    inv_delta = 1 / delta;
    vec3_sub(&tvec, &RAY_ORIGIN(r), &triangle->v0);
    hit->u = vec3_dot(&tvec, &pvec) * inv_delta;
    if (hit->u < 0 || hit->u > 1)
        return (FALSE);
    vec3_cross(&qvec, &tvec, &v0v1);
    hit->v = vec3_dot(&RAY_DIRECTION(r), &qvec) * inv_delta;
    if (hit->v < 0 || ((hit->v + hit->u) > 1))
        return (FALSE);
    hit->t = vec3_dot(&v0v2, &qvec) * inv_delta;
    ray_point_at(&hit->pos, r, hit->t);
    vec3_assign(&hit->normal, &normal);
    return (TRUE);
}

t_bool      rectangle_hit(t_entity *entity, const t_ray *r, t_precision precision, t_hit_record *hit)
{
    t_primitive_rectangle *rectangle = (t_primitive_rectangle *)entity->data;
    float ddota, ddotb;
    t_vec3  tmp, normal, pos, d;
    float t;

    vec3_cross(&normal, &rectangle->a, &rectangle->b);
    vec3_normalize(&normal);

    vec3_sub(&tmp, &rectangle->p0, &RAY_ORIGIN(r));
    t = vec3_dot(&tmp, &normal) / vec3_dot(&RAY_DIRECTION(r), &normal);
    if (t <= precision.min)
        return (FALSE);
    vec3_mul_f(&pos, &RAY_DIRECTION(r), t);
    vec3_add(&pos, &pos, &RAY_ORIGIN(r));
    vec3_sub(&d, &pos, &rectangle->p0);
    ddota = vec3_dot(&d, &rectangle->a);
    if (ddota < 0.0 || ddota > vec3_squared_length(&rectangle->a))
        return (FALSE);
    ddotb = vec3_dot(&d, &rectangle->b);
    if (ddotb < 0.0 || ddotb > vec3_squared_length(&rectangle->b))
        return (FALSE);
    hit->t = t;
    vec3_assign(&hit->normal, &normal);
    vec3_assign(&hit->pos, &pos);
    /**
     * u = (p - p0) . a / |a|
     * v = (p - p0) . b / |b|
     */
    vec3_sub(&tmp, &hit->pos, &rectangle->p0);
    hit->u = vec3_dot(&tmp, &rectangle->a) / vec3_squared_length(&rectangle->a);
    hit->v = vec3_dot(&tmp, &rectangle->b) / vec3_squared_length(&rectangle->b);
    return (TRUE);
}

const t_vec3    g_cube_normals[6] = {
        {-1, 0, 0}, //-x
        {0, -1, 0}, //-y
        {0, 0, -1}, //-z
        {1, 0, 0}, //+x
        {0, 1, 0}, //+y
        {0, 0, 1} //+z
};

t_bool      box_hit(t_entity *entity, const t_ray *r, t_precision precision, t_hit_record *hit)
{
    int     face_in, face_out;
    t_primitive_box *box = (t_primitive_box *)entity->data;
    t_vec3 min, max, o, d;
    float a, b, c, t0, t1;

    vec3_assign(&o, &RAY_ORIGIN(r));
    vec3_assign(&d, &RAY_DIRECTION(r));
    a = 1.0f / d.x;
    if (a >= 0)
    {
        min.x = (box->a.x - o.x) * a;
        max.x = (box->b.x - o.x) * a;
    }
    else
    {
        min.x = (box->b.x - o.x) * a;
        max.x = (box->a.x - o.x) * a;
    }
    b = 1.0f / d.y;
    if (b >= 0)
    {
        min.y = (box->a.y - o.y) * b;
        max.y = (box->b.y - o.y) * b;
    }
    else
    {
        max.y = (box->a.y - o.y) * b;
        min.y = (box->b.y - o.y) * b;
    }
    c = 1.0f / d.z;
    if (c >= 0)
    {
        min.z = (box->a.z - o.z) * c;
        max.z = (box->b.z - o.z) * c;
    }
    else
    {
        min.z = (box->b.z - o.z) * c;
        max.z = (box->a.z - o.z) * c;
    }
    if (min.x > min.y)
    {
        t0 = min.x;
        face_in = (a >= 0.0) ? 0 : 3;
    }
    else
    {
        t0 = min.y;
        face_in = (b >= 0.0) ? 1 : 4;
    }
    if (min.z > t0)
    {
        t0 = min.z;
        face_in = (c >= 0.0) ? 2 : 5;
    }
    if (max.x < max.y)
    {
        t1 = max.x;
        face_out = (a >= 0.0) ? 3 : 0;
    }
    else
    {
        t1 = max.y;
        face_out = (b >= 0.0) ? 4 : 1;
    }
    if (max.z < t1)
    {
        t1 = max.z;
        face_out = (c >= 0.0) ? 5 : 2;
    }
    if (t0 < t1 && t1 > precision.min)
    {
        if (t0 > precision.min)
        {
            hit->t = t0;
            vec3_assign(&hit->normal, &g_cube_normals[face_in]);
        }
        else
        {
            hit->t = t1;
            vec3_assign(&hit->normal, &g_cube_normals[face_out]);
        }
        vec3_mul_f(&hit->pos, &RAY_DIRECTION(r), hit->t);
        vec3_add(&hit->pos, &hit->pos, &RAY_ORIGIN(r));
        return (TRUE);
    }
    else
        return (FALSE);
}