//
// Created by Raphaël Dantzer on 24/06/16.
//

#include <stdio.h>
#include "safe_alloc.h"
#include "libft/includes/libft.h"

void    *safe_alloc(size_t length)
{
    void *tmp;

    tmp = ft_memalloc(length);
    if (!tmp)
    {
        ft_putendl("Allocation failed");
        exit(EXIT_FAILURE);
    }
    else
        return (tmp);
}