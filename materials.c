//
// Created by Raphaël Dantzer on 27/06/16.
//

#include "rt.h"

static t_vec3 random_in_unit_sphere()
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

static t_bool   refract(const t_vec3 *v1, const t_vec3 *v2, float ni_over_nt, t_vec3 *refracted)
{
    t_vec3      uv;
    t_vec3      tmp;
    float       dt;
    float       delta;

    vec3_unit_vector(&uv, v1);
    dt = vec3_dot(&uv, v1);
    delta = 1.0f - SQR(ni_over_nt) * (1 - SQR(dt));
    if (delta > 0)
    {
        vec3_sub(&tmp, v1, vec3_mul_f(&tmp, v2, dt));
        vec3_mul_f(&uv, v2, sqrtf(delta));
        vec3_sub(refracted, &tmp, &uv);
        return (TRUE);
    }
    else
        return (FALSE);
}

static float    schlick(float cosine, float ref_idx)
{
    float       r;

    r = (1 - ref_idx) / (1 + ref_idx);
    r = SQR(r);
    return (r + (1 - r) * powf((1 - cosine), 5));
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
#define REF_IDX 2.4f

t_bool          dielectric(t_material *material, const t_ray *r, const t_hit_record *h, t_vec3 *attenuation, t_ray *scattered)
{
    t_vec3      outward_normal;
    t_vec3      reflected;
    t_vec3      refracted;
    float       ni_over_nt;
    float       reflect_probe;
    float       cosine;

    vec3_reflect(&reflected, &RAY_DIRECTION(r), &h->normal);
    vec3_assign(attenuation, &material->albedo);
    if (vec3_dot(&RAY_DIRECTION(r), &h->normal) > 0)
    {
        vec3_mul_f(&outward_normal, &h->normal, -1.f);
        //TODO pass idx
        ni_over_nt = REF_IDX;
        cosine = REF_IDX * vec3_dot(&RAY_DIRECTION(r), &h->normal) / vec3_length(&RAY_DIRECTION(r));
    }
    else
    {
        vec3_assign(&outward_normal, &h->normal);
        ni_over_nt = 1.0f / REF_IDX;
        cosine = - vec3_dot(&RAY_DIRECTION(r), &h->normal) / vec3_length(&RAY_DIRECTION(r));
    }
    if (refract(&RAY_DIRECTION(r), &outward_normal, ni_over_nt, &refracted))
        reflect_probe = schlick(cosine, REF_IDX);
    else
        reflect_probe = 1.0f;
    if (drand48() < reflect_probe)
        ray_assign(scattered, &h->pos, &reflected);
    else
        ray_assign(scattered, &h->pos, &refracted);
    return (TRUE);
}