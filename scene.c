//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "rt.h"
#include "libft/includes/libft.h"
#include "safe_alloc.h"

void        scene_init(t_scene *scene, int entity_count)
{
    ft_bzero(scene, sizeof(t_scene));
    scene->entity_count = entity_count;
    scene->entities = (t_entity **)safe_alloc(sizeof(t_entity *) * entity_count);
}

t_bool       scene_raytrace(t_scene *scene, const t_ray *r, t_precision p, t_hit_record *h)
{
    t_bool          collision;
    float           closest;
    int             i;

    closest = p.max;
    collision = FALSE;
    i = -1;
    while (++i < scene->entity_count)
    {
        if (scene->entities[i]->hit(scene->entities[i], r, p, h))
        {
            collision = TRUE;
            closest = h->t;
        }
    }
    return (collision);
}