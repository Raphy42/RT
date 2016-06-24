//
// Created by Raphaël Dantzer on 24/06/16.
//

#ifndef RAYTRACER_RT_H
#define RAYTRACER_RT_H

#include <SDL.h>
#include "m3d.h"

#define WIN_X 1200
#define WIN_Y 600

typedef struct      s_canvas
{
    SDL_Texture     *image;
    Uint32          *image_pointer;
}                   t_canvas;

typedef struct      s_window
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Event       event;
    t_canvas        canvas;
}                   t_window;

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


#endif //RAYTRACER_RT_H
