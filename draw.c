//
// Created by Raphaël Dantzer on 24/06/16.
//

#include "m3d.h"
#include "rt.h"

void        draw_pixel(int x, int y, t_rgb color, t_canvas *canvas)
{
    canvas->image_pointer[WIN_X * y + x] = (Uint32 )((color.r << 16) + (color.g << 8) + color.b);
}

void        render(t_window *w)
{
    SDL_UpdateTexture(w->canvas.image, NULL, w->canvas.image_pointer, WIN_X * sizeof(Uint32));
    SDL_RenderCopy(w->renderer, w->canvas.image, NULL, NULL);
    SDL_RenderPresent(w->renderer);
}