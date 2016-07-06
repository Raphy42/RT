//
// Created by Raphaël Dantzer on 28/06/16.
//

#include <SDL_render.h>
#include "pipeline.h"
#include "libft/includes/libft.h"
#include "rt.h"

t_vec3   *albedo(t_texture *texture, const t_hit_record *h, t_vec3 *color)
{
    (void)h;
    return (vec3_assign(color, &texture->albedo));
}

t_vec3  *debug(t_texture *texture, const t_hit_record *h, t_vec3 *color)
{
    (void)texture;
    return (vec3_assign(color, vec3_mul_f(color, vec3_add_f(color, &h->normal, 1.0f), .5f)));
}

t_vec3  *checker(t_texture *texture, const t_hit_record *h, t_vec3 *color)
{
    (void)texture;
    float   sines;

    vec3_clear(color);
    sines = sinf(10 * h->pos.x) *  sinf(10 * h->pos.y) * sinf(10 * h->pos.z);
    if (sines < 0)
        return (color);
    else
        return (vec3_assign(color, &g_vec3_identity));
}

t_vec3  *rainbow(t_texture *texture, const t_hit_record *h, t_vec3 *color)
{
    (void)texture;
    vec3_assign(color, vec3_mul_f(color, vec3_add_f(color, &h->normal, 1.0f), .5f));
    color->x = sinf(color->x * .1f);
    color->y = sinf(color->y * .1f);
    color->z = sinf(color->z * .1f);
    return (color);
}

t_vec3   *texture_map(t_texture *texture, const t_hit_record *h, t_vec3 *color)
{
    int i = (int)(h->u * (float)texture->image->w);
    int j = (int)((1.f - h->v) * (float)texture->image->h - 0.001f);

    if (j < 0)
        j = 0;
    if (i < 0)
        i = 0;
    if (i > texture->image->w - 1)
        i = texture->image->w - 1;
    if (j > texture->image->h - 1)
        j = texture->image->h - 1;
    color->x = texture->image->data[texture->image->n * i + texture->image->n * texture->image->w * j] / 255.f;
    color->y = texture->image->data[texture->image->n * i + texture->image->n * texture->image->w * j + 1] / 255.f;
    color->z = texture->image->data[texture->image->n * i + texture->image->n * texture->image->w * j + 2] / 255.f;
    return (color);
}