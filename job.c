//
// Created by Raphaël Dantzer on 16/07/16.
//

#include <assert.h>
#include "thread_pool.h"
#include "libft/includes/libft.h"

t_job    *job_queue_pull(t_thread_pool *thread_pool)
{
    t_job       *job;

    job = thread_pool->queue->first;
    if (thread_pool->queue->size == 1)
    {
        thread_pool->queue->first = NULL;
        thread_pool->queue->last = NULL;
        thread_pool->queue->size = 0;
    }
    else if (thread_pool->queue->size != 0)
    {
        thread_pool->queue->first = job->prev;
        thread_pool->queue->size--;
        semaphore_post(thread_pool->queue->has_jobs);
    }
    return (job);
}

void     job_queue_push(t_thread_pool *thread_pool, t_job *job)
{
    job->prev = NULL;
    if (thread_pool->queue->size == 0)
    {
        thread_pool->queue->first = job;
        thread_pool->queue->last = job;
    }
    else
    {
        thread_pool->queue->last->prev = job;
        thread_pool->queue->last = job;
    }
    thread_pool->queue->size++;
    semaphore_post(thread_pool->queue->has_jobs);
}

static void     job_queue_clear(t_thread_pool *thread_pool)
{
    while (thread_pool->queue->size)
        free(job_queue_pull(thread_pool));
    thread_pool->queue->first = NULL;
    thread_pool->queue->last = NULL;
    semaphore_reset(thread_pool->queue->has_jobs);
    thread_pool->queue->size = 0;
}

int             job_queue_init(t_thread_pool *thread_pool)
{
    thread_pool->queue = (t_job_queue *)ft_memalloc(sizeof(t_job_queue));
    if (!thread_pool->queue)
        return (-1);
    thread_pool->queue->has_jobs = (t_semaphore *)ft_memalloc(sizeof(t_semaphore));
    if (!thread_pool->queue->has_jobs)
        return (-1);
    pthread_mutex_init(&(thread_pool->queue->rw), NULL);
    semaphore_init(thread_pool->queue->has_jobs, 0);
    return (0);
}

void            job_queue_destroy(t_thread_pool *thread_pool)
{
    job_queue_clear(thread_pool);
    free(thread_pool->queue->has_jobs);
}