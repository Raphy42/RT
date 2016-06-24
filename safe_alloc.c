//
// Created by Raphaël Dantzer on 24/06/16.
//

#include <stdio.h>
#include "safe_alloc.h"
#include "libft/includes/libft.h"

static t_allocation_table           **allocation_table(void)
{
    static t_allocation_table       *table;

    return (&table);
}

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

void    safe_alloc_free_registered(void)
{
    t_allocation_table  *t;
    t_allocation_table  *t1;

    t = (*allocation_table());
    while (t->next)
    {
        free(t->address);
        t1 = t;
        t = t->next;
        free(t);
    }
}