//
// Created by Raphaël Dantzer on 11/07/16.
//

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H

#include "m3d.h"

typedef struct      s_aabb
{
    t_vec3          min;
    t_vec3          max;
}                   t_aabb;

#endif //RAYTRACER_AABB_H
