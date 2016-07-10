//
// Created by Raphael DANTZER on 6/28/16.
//

#ifndef RAYTRACER_ENTITY_H
#define RAYTRACER_ENTITY_H

#include "m3d.h"

typedef struct      s_primitive_sphere
{
    //TODO add pos to sphere
    t_vec3          pos;
    float           radius;
}                   t_primitive_sphere;

typedef struct      s_primitive_triangle
{
    t_vec3          v0;
    t_vec3          v1;
    t_vec3          v2;
}                   t_primitive_triangle;

typedef struct      s_primitive_rectangle
{
    t_vec3          p0;
    t_vec3          a;
    t_vec3          b;
}                   t_primitive_rectangle;

typedef struct      s_primitive_box
{
    t_vec3          a;
    t_vec3          b;
}                   t_primitive_box;

t_primitive_sphere      *sphere_create(float radius);
t_primitive_triangle    *triangle_create(const t_vec3 *v0, const t_vec3 *v1, const t_vec3 *v2);
t_primitive_rectangle   *rectangle_create(const t_vec3 *p0, const t_vec3 *a, const t_vec3 *b);
t_primitive_box     *box_create(const t_vec3 *a, const t_vec3 *b);

#endif //RAYTRACER_ENTITY_H
