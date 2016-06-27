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
    scene->entities = (t_entity **)ft_memalloc(sizeof(t_entity *) * entity_count);
}

t_bool       scene_raytrace(t_scene *scene, const t_ray *r, t_precision p, t_hit_record *h)
{
    t_bool          collision;
    int             i;
    t_precision     tmp;
    t_hit_record    tmp_record;

    ft_bzero(&tmp_record, sizeof(t_hit_record));
    ft_memcpy(&tmp, &p, sizeof(t_precision));
    collision = FALSE;
    i = -1;
    while (++i < scene->entity_count)
    {
        if (scene->entities[i]->hit(scene->entities[i], r, tmp, h))
        {
            h->material = scene->entities[i]->material;
            collision = TRUE;
            tmp.max = h->t;
        }
    }
    return (collision);
}