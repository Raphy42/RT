//
// Created by Raphaël Dantzer on 24/06/16.
//

#include <assert.h>
#include "rt.h"
#include "libft/includes/libft.h"

static void init_sdl_context(t_window *w)
{
    SDL_Init(SDL_INIT_VIDEO);
    assert(w->window = SDL_CreateWindow("TODO MODIFY INIT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_X, WIN_Y, SDL_WINDOW_SHOWN));
    assert(w->renderer = SDL_CreateRenderer(w->window, -1, SDL_RENDERER_ACCELERATED));
    assert(w->canvas.image_pointer = (Uint32 *)ft_memalloc(WIN_X * WIN_Y * sizeof(Uint32)));
    assert(w->canvas.image = SDL_CreateTexture(w->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_X, WIN_Y));
}

void        init(t_window *w)
{
    ft_bzero(w, sizeof(t_window));
    init_sdl_context(w);
}