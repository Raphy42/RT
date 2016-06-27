//
// Created by Raphaël Dantzer on 24/06/16.
//

#ifndef RAYTRACER_RT_H
#define RAYTRACER_RT_H

#include <SDL.h>
#include "m3d.h"

#define WIN_X 400
#define WIN_Y 200
#define WIN_NS 1000

#ifndef TRUE
# define TRUE 1
#endif

#ifndef FALSE
# define FALSE 0
#endif

#ifndef MAXFLOAT
# define MAXFLOAT    0x1.fffffep+127f
#endif

typedef int         t_bool;

/**
 * SDL2 image structure
 */
typedef struct      s_canvas
{
    SDL_Texture     *image;
    Uint32          *image_pointer;
}                   t_canvas;

/**
 * SDL2 context
 */
typedef struct      s_window
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Event       event;
    t_canvas        canvas;
}                   t_window;

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


typedef struct s_material t_material;
/**
 * Raytracer hit record
 */
typedef struct      s_hit_record
{
    float           t;
    t_vec3          pos;
    t_vec3          normal;
    t_material      *material;
}                   t_hit_record;

/**
 * Material struct
 */
typedef struct      s_material
{
    t_material_type type;
    t_vec3          albedo;
    t_bool          (*scatter)(struct s_material *, const t_ray *, const t_hit_record *, t_vec3 *, t_ray *);
}                   t_material;

/**
 * Entity type
 */
typedef enum        e_entity_type
{
    PRIMITIVE_SPHERE = 0,
}                   t_entity_type;

/**
 * Entity structure with pseudo method hit
 */
typedef struct      s_entity
{
    t_entity_type   type;
    t_vec3          center;
    float           radius;
    t_bool          (*hit)(struct s_entity *, const t_ray *, t_precision, t_hit_record *);
    t_material      *material;
}                   t_entity;

/**
 * Camera structure
 */
typedef struct      s_camera
{
    t_vec3          eye;
    t_vec3          center;
    t_vec3          p_up;
    float           fov;
    float           aspect;
    t_vec3          lower_left_corner;
    t_vec3          horizontal;
    t_vec3          vertical;
}                   t_camera;

typedef struct      s_scene
{
    t_entity        **entities;
    int             entity_count;
}                   t_scene;
/**
 * INIT.c
 */
void        init(t_window *w);

/**
 * DRAW.c
 */
void        draw_pixel(int x, int y, t_rgb color, t_canvas *canvas);
void        render(t_window *w);

/**
 * EVENTS.c
 */
void        handle_events(SDL_Event event);

/**
 * RAYTRACE.c
 */
t_bool      sphere_hit(t_entity *entity, const t_ray *r, t_precision precision, t_hit_record *hit);

/**
 * CAMERA.c
 */
void        camera_init(t_camera *camera);
t_ray       camera_get_ray(t_camera *camera, float u, float v);

/**
 * MATERIALS.c
 */
t_bool      lambertian(t_material *material, const t_ray *r, const t_hit_record *h, t_vec3 *attenuation, t_ray *scattered);
t_bool      metal(t_material *material, const t_ray *r, const t_hit_record *h, t_vec3 *attenuation, t_ray *scattered);
t_bool      dielectric(t_material *material, const t_ray *r, const t_hit_record *h, t_vec3 *attenuation, t_ray *scattered);

#endif //RAYTRACER_RT_H
