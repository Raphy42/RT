//
// Created by Raphael DANTZER on 7/10/16.
//

#include "octree.h"
#include "libft/includes/libft.h"
#include "rt.h"

t_octree    *octree_create(const t_vec3 *origin, const t_vec3 *half_dimension)
{
    t_octree    *o;

    o = (t_octree *)ft_memalloc(sizeof(t_octree));
    vec3_assign(&o->origin, origin);
    vec3_assign(&o->half_dimension, half_dimension);
    return (o);
}

void        octree_destroy(t_octree *octree)
{
    int     i;

    i = -1;
    while (++i < 8 && octree->children[i])
        octree_destroy(octree->children[i]);
    free(octree);
}

int         octree_get_octant(t_octree *octree, const t_vec3 *point)
{
    int     octant;

    octant = 0;
    if (point->x >= octree->origin.x)
        octant |= 4;
    if (point->y >= octree->origin.y)
        octant |= 2;
    if (point->z >= octree->origin.z)
        octant |= 1;
    return (octant);
}

static inline t_bool      octree_is_leaf_node(t_octree *octree)
{
    return (octree->children[0] == NULL);
}

void        octree_insert(t_octree *octree, t_octree_data *data)
{
    t_octree_data   *tmp;
    int     i;
    t_vec3  origin;
    t_vec3  half_dimension;

    i = -1;
    if (octree_is_leaf_node(octree))
    {
        if (octree->data == NULL)
        {
            octree->data = data;
            return ;
        }
        else
        {
            tmp = data;
            data = NULL;
            while (++i < 8)
            {
                vec3_assign(&origin, &octree->origin);
                origin.x += octree->half_dimension.x * (i & 4 ? .5f : -.5f);
                origin.y += octree->half_dimension.y * (i & 2 ? .5f : -.5f);
                origin.z += octree->half_dimension.z * (i & 1 ? .5f : -.5f);
                vec3_mul_f(&half_dimension, &octree->half_dimension, .5f);
                octree->children[i] = octree_create(&origin, &half_dimension);
            }
            octree_insert(octree->children[octree_get_octant(octree, &tmp->pos)], tmp);
            octree_insert(octree->children[octree_get_octant(octree, &octree->data->pos)], data);
        }
    }
    else
        octree_insert(octree->children[octree_get_octant(octree, &data->pos)], data);
}