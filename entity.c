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

t_entity        *entity_create(t_entity_type type, t_material *material, const t_vec3 *pos, void *data)
{
    t_entity    *entity;

    entity = (t_entity *)ft_memalloc(sizeof(t_entity));
    entity->type = type;
    if (type == PRIMITIVE_SPHERE)
        entity->hit = &sphere_hit;
    else if (type == PRIMITIVE_TRIANGLE)
        entity->hit = &triangle_hit;
    entity->material = material;
    vec3_assign(&entity->center, pos);
    entity->data = data;
    return (entity);
}

t_material      *material_create(t_material_type type, t_vec3 *albedo)
{
    t_material  *material;

    material = (t_material *)ft_memalloc(sizeof(t_material));
    material->type = type;
    vec3_assign(&material->texture.albedo, albedo);
    if (material->type == MATERIAL_LAMBERTIAN)
        material->scatter = &lambertian;
    else if (material->type == MATERIAL_METAL)
        material->scatter = &metal;
    else if (material->type == MATERIAL_DIELECTRIC)
        material->scatter = &dielectric;
    else if (material->type == MATERIAL_DEBUG)
    {
        material->scatter = &debug_test;
        material->texture.value = &debug;
    }
    return (material);
}