//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "rt.h"
#include "safe_alloc.h"

t_entity        *entity_create(t_entity_type type, const t_vec3 *pos, float radius)
{
    t_entity    *entity;

    entity = (t_entity *)safe_alloc(sizeof(t_entity));
    entity->type = type;
    vec3_assign(&entity->center, pos);
    entity->radius = radius;
    return (entity);
}