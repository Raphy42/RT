//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "rt.h"
#include "safe_alloc.h"
#include "entity.h"

t_primitive_sphere  *sphere_create(float radius)
{
    t_primitive_sphere  *s;

    s = (t_primitive_sphere *)ft_memalloc(sizeof(t_primitive_sphere));
    s->radius = radius;
    return (s);
}

t_primitive_triangle    *triangle_create(const t_vec3 *v0, const t_vec3 *v1, const t_vec3 *v2)
{
    t_primitive_triangle    *t;

    t = (t_primitive_triangle *)ft_memalloc(sizeof(t_primitive_triangle));
    vec3_assign(&t->v0, v0);
    vec3_assign(&t->v1, v1);
    vec3_assign(&t->v2, v2);
    return (t);
}

t_primitive_rectangle   *rectangle_create(const t_vec3 *p0, const t_vec3 *a, const t_vec3 *b)
{
    t_primitive_rectangle   *r;

    r = (t_primitive_rectangle *)ft_memalloc(sizeof(t_primitive_rectangle));
    vec3_assign(&r->p0, p0);
    vec3_assign(&r->a, a);
    vec3_assign(&r->b, b);
    return (r);
}

t_primitive_box     *box_create(const t_vec3 *a, const t_vec3 *b)
{
    t_primitive_box *box;

    box = (t_primitive_box *)ft_memalloc(sizeof(t_primitive_box));
    if (a->x < b->x && a->y < b->y && a->z < b->z)
    {
        vec3_assign(&box->a, a);
        vec3_assign(&box->b, b);
    }
    else
    {
        vec3_assign(&box->a, b);
        vec3_assign(&box->b, a);
    }
    return (box);
}

t_entity        *entity_create(t_entity_type type, t_material *material, const t_vec3 *pos, void *data)
{
    t_entity    *entity;

    entity = (t_entity *)ft_memalloc(sizeof(t_entity));
    entity->type = type;
    if (type == PRIMITIVE_SPHERE)
    {
        vec3_assign(&entity->center, pos);
        entity->hit = &sphere_hit;
    }
    else if (type == PRIMITIVE_TRIANGLE)
        entity->hit = &triangle_hit;
    else if (type == PRIMITIVE_RECTANGLE)
        entity->hit = &rectangle_hit;
    else if (type == PRIMITIVE_AXIS_ALIGNED_BOX)
        entity->hit = &box_hit;
    entity->material = material;
    entity->data = data;
    return (entity);
}

t_material      *material_create(t_material_type type, t_vec3 *albedo_t)
{
    t_material  *material;

    material = (t_material *)ft_memalloc(sizeof(t_material));
    material->type = type;
    vec3_assign(&material->texture.albedo, albedo_t);
    if (material->type == MATERIAL_LAMBERTIAN)
    {
        material->scatter = &lambertian;
        material->texture.value = &albedo;
    }
    else if (material->type == MATERIAL_METAL)
        material->scatter = &metal;
    else if (material->type == MATERIAL_DIELECTRIC)
        material->scatter = &dielectric;
    else if (material->type == MATERIAL_DEBUG)
    {
        material->scatter = &lambertian;
        material->texture.value = &debug;
    }
    else if (material->type == MATERIAL_EMITTER)
    {
        material->scatter = &emitter;
        material->emit = &basic_light;
    }
    return (material);
}