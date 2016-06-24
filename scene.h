//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "rt.h"

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

/**
 * ENTITY.c
 */
t_entity        *entity_create(t_entity_type type, const t_vec3 *pos, float radius);

/**
 * SCENE.c
 */
void        scene_init(t_scene *scene, int entity_count);
t_bool      scene_raytrace(t_scene *scene, const t_ray *r, t_precision p, t_hit_record *h);

#endif //RAYTRACER_SCENE_H
