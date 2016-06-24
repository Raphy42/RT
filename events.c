//
// Created by Raphaël Dantzer on 24/06/16.
//

#include <SDL_events.h>

void        handle_events(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
        if (event.key.keysym.sym == SDLK_ESCAPE)
            exit(EXIT_SUCCESS);
}