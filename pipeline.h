//
// Created by Raphaël Dantzer on 28/06/16.
//

#ifndef RAYTRACER_PIPELINE_H
#define RAYTRACER_PIPELINE_H

#include "m3d.h"

typedef struct s_material t_material;
typedef struct s_hit_record t_hit_record;

typedef enum    e_texture_type
{
    TEXTURE_DEBUG = 0,
    TEXTURE_ALBEDO,
    TEXTURE_CHECKER
}               t_texture_type;

typedef struct  s_texture
{
    t_vec3          albedo;
    float           fuzzyness;
    t_texture_type  type;
    t_vec3          *(*value)(struct s_texture *, const t_hit_record *, t_vec3 *);
    t_vec3          color;
}               t_texture;

/**
 * Precision for hit function
 */
typedef struct      s_precision
{
    float           min;
    float           max;
}                   t_precision;

typedef enum        e_material_type
{
    MATERIAL_DEBUG = 0,
    MATERIAL_LAMBERTIAN,
    MATERIAL_METAL,
    MATERIAL_DIELECTRIC
}                   t_material_type;

/**
 * Raytracer hit record
 */
typedef struct      s_hit_record
{
    float           t;
    t_vec3          pos;
    t_vec3          normal;
    t_material      *material;
    float           u;
    float           v;
}                   t_hit_record;

/**
 * Material struct
 */
typedef struct      s_material
{
    t_material_type type;
    int             (*scatter)(struct s_material *, const t_ray *, const t_hit_record *, t_vec3 *, t_ray *);
    t_texture       texture;
}                   t_material;

/**
 * Entity type
 */
typedef enum        e_entity_type
{
    PRIMITIVE_SPHERE = 0,
    PRIMITIVE_PLANE,
    PRIMITIVE_TRIANGLE,
}                   t_entity_type;

/**
 * Entity structure with pseudo method hit
 */
typedef struct      s_entity
{
    t_entity_type   type;
    t_vec3          center;
    float           radius;
    int             (*hit)(struct s_entity *, const t_ray *, t_precision, t_hit_record *);
    t_material      *material;
    void            *data;
}                   t_entity;

/**
 * TEXTURE.c
 */
t_vec3   *albedo(t_texture *texture, const t_hit_record *h, t_vec3 *color);
t_vec3   *debug(t_texture *texture, const t_hit_record *h, t_vec3 *color);
t_vec3   *checker(t_texture *texture, const t_hit_record *h, t_vec3 *color);
t_vec3   *rainbow(t_texture *texture, const t_hit_record *h, t_vec3 *color);

#endif //RAYTRACER_PIPELINE_H
