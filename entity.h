//
// Created by Raphael DANTZER on 6/28/16.
//

#ifndef RAYTRACER_ENTITY_H
#define RAYTRACER_ENTITY_H

#include "m3d.h"

typedef struct      s_primitive_sphere
{
    float           radius;
}                   t_primitive_sphere;

typedef struct      s_primitive_triangle
{
    t_vec3          v0;
    t_vec3          v1;
    t_vec3          v2;
}                   t_primitive_triangle;


t_primitive_sphere  *sphere_create(float radius);
t_primitive_triangle    *triangle_create(const t_vec3 *v0, const t_vec3 *v1, const t_vec3 *v2);

#endif //RAYTRACER_ENTITY_H
