//
// Created by Raphael DANTZER on 7/10/16.
//

#ifndef RAYTRACER_OCTREE_H
#define RAYTRACER_OCTREE_H

#include "m3d.h"

typedef struct      s_octree_data
{
    t_vec3          pos;
    void            *data;
}                   t_octree_data;

typedef struct      s_octree
{
    t_vec3          origin;
    t_vec3          half_dimension;
    struct s_octree *children[8];
    t_octree_data   *data;
}                   t_octree;

void        octree_insert(t_octree *octree, t_octree_data *data);
int         octree_get_octant(t_octree *octree, const t_vec3 *point);
void        octree_destroy(t_octree *octree);
t_octree    *octree_create(const t_vec3 *origin, const t_vec3 *half_dimension);

#endif //RAYTRACER_OCTREE_H
