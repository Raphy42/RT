//
// Created by Raphaël Dantzer on 24/06/16.
//

#ifndef RAYTRACER_RT_H
#define RAYTRACER_RT_H

#include <SDL.h>
#include "m3d.h"

#define WIN_X 1200
#define WIN_Y 600
#define WIN_NS 100

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
 * Raytracer hit record
 */
typedef struct      s_hit_record
{
    float           t;
    t_vec3          pos;
    t_vec3          normal;
}                   t_hit_record;

/**
 * Precision for hit function
 */
typedef struct      s_precision
{
    float           min;
    float           max;
}                   t_precision;

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
}                   t_entity;

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

#endif //RAYTRACER_RT_H
