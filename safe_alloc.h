//
// Created by Raphaël Dantzer on 24/06/16.
//

#ifndef RAYTRACER_SAFE_ALLOC_H
#define RAYTRACER_SAFE_ALLOC_H

#include "libft/includes/libft.h"

typedef enum        s_allocation_type
{
    ALLOC_TYPE_ENTITY = 0,
    ALLOC_TYPE_DEBUG,
}                   t_allocation_type;

typedef struct      s_allocation_table
{
    void                        *address;
    size_t                      index;
    size_t                      size;
    t_allocation_type           type;
    struct s_allocation_table   *next;
}                   t_allocation_table;

void    *safe_alloc_register(void *address, size_t size, t_allocation_type type);
void    *safe_alloc(size_t length);
void    safe_alloc_free_registered(void);

#endif //RAYTRACER_SAFE_ALLOC_H
