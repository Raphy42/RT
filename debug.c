//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "debug.h"

void    vec3_pretty_print(const t_vec3 *v)
{
    ft_fprintf(2, "{%f, %f, %f}\n", v->x, v->y, v->z);
}
