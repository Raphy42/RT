//
// Created by Raphaël Dantzer on 29/06/16.
//

#include "m3d.h"
#include "pipeline.h"

t_vec3          *basic_light(struct s_material *material, const t_hit_record *hit_record, t_vec3 *p)
{
    (void)hit_record;
    (void)p;
    return (vec3_assign(p, &material->texture.emit_color));
}