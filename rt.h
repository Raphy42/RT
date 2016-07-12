//
// Created by Raphaël Dantzer on 24/06/16.
//
#ifndef RAYTRACER_RT_H
#define RAYTRACER_RT_H

#include <SDL.h>
#include "m3d.h"
#include "pipeline.h"

#define WIN_X       1200
#define WIN_Y       600
#define WIN_NS      1
#define RT_THREADS  8
#define RT_ROWS     8

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
    t_camera        *camera;
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
t_bool      triangle_hit(t_entity *entity, const t_ray *r, t_precision precision, t_hit_record *hit);
t_bool      rectangle_hit(t_entity *entity, const t_ray *r, t_precision precision, t_hit_record *hit);
t_bool      box_hit(t_entity *entity, const t_ray *r, t_precision precision, t_hit_record *hit);

/**
 * CAMERA.c
 */
t_camera    *camera_init();
void        camera_get_ray(t_ray *ray, t_camera *camera, float u, float v);

/**
 * MATERIALS.c
 */
t_bool      lambertian(t_material *material, const t_ray *r, const t_hit_record *h, t_vec3 *attenuation, t_ray *scattered);
t_bool      metal(t_material *material, const t_ray *r, const t_hit_record *h, t_vec3 *attenuation, t_ray *scattered);
t_bool      dielectric(t_material *material, const t_ray *r, const t_hit_record *h, t_vec3 *attenuation, t_ray *scattered);
t_bool      debug_test(t_material *material, const t_ray *r, const t_hit_record *h, t_vec3 *attenuation, t_ray *scattered);
t_bool      emitter(t_material *material, const t_ray *r, const t_hit_record *h, t_vec3 *attenuation, t_ray *scattered);

/**
 * LIGHT.c
 */
t_vec3          *basic_light(struct s_material *material, const t_hit_record *hit_record, t_vec3 *p);

/**
 * THREAD.c
 */
void    threaded_render(t_scene *scene, t_window *w, int width, int height);

#endif //RAYTRACER_RT_H
