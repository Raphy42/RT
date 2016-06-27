//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "rt.h"
#include "safe_alloc.h"

t_entity        *entity_create(t_entity_type type, t_material *material, const t_vec3 *pos, float radius)
{
    t_entity    *entity;

    entity = (t_entity *)ft_memalloc(sizeof(t_entity));
    entity->type = type;
    entity->hit = &sphere_hit;
    entity->material = material;
    vec3_assign(&entity->center, pos);
    entity->radius = radius;
    return (entity);
}

t_material      *material_create(t_material_type type, t_vec3 *albedo)
{
    t_material  *material;

    material = (t_material *)ft_memalloc(sizeof(t_material));
    material->type = type;
    vec3_assign(&material->albedo, albedo);
    if (material->type == MATERIAL_LAMBERTIAN)
        material->scatter = &lambertian;
    else if (material->type == MATERIAL_METAL)
        material->scatter = &metal;
    return (material);
}