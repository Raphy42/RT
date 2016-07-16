//
// Created by Raphaël Dantzer on 16/07/16.
//

#include <assert.h>
#include "thread_pool.h"
#include "libft/includes/libft.h"

static void         thread_hold(int signal)
{
    g_threads_on_hold   = 1;

    (void)signal;
    while (g_threads_on_hold)
        sleep(1);
}

static void         *thread_do(t_thread *thread)
{
    struct sigaction    act;
    t_thread_pool       *pool;
    t_job               *job;

    pool = thread->pool;
    sigemptyset(&act.sa_mask);
    act.sa_handler = thread_hold;
    act.sa_flags = 0;
    if (sigaction(SIGUSR1, &act, NULL) == -1)
        ft_putendl_fd("thread_do: Unable to handle SIGUSR1", 2);
    pthread_mutex_lock(&pool->lock);
    pool->alive++;
    pthread_mutex_unlock(&pool->lock);
    while (g_threads_keepalive)
    {
        semaphore_wait(pool->queue->has_jobs);
        if (g_threads_keepalive)
        {
            pthread_mutex_lock(&pool->lock);
            pool->working++;
            pthread_mutex_unlock(&pool->lock);
            pthread_mutex_lock(&pool->queue->rw);
            job = job_queue_pull(pool);
            pthread_mutex_unlock(&pool->queue->rw);
            if (job)
            {
                job->task(job->arg);
                //TODO check if job must be deleted
                free(job);
            }
            pthread_mutex_lock(&pool->lock);
            pool->working--;
            if (!pool->working)
                pthread_cond_signal(&pool->all_idle);
            pthread_mutex_unlock(&pool->lock);
        }
    }
    pthread_mutex_lock(&pool->lock);
    pool->alive--;
    pthread_mutex_unlock(&pool->lock);
    return (NULL);
}

static void         thread_destroy(t_thread *thread)
{
    free(thread);
}

static int          thread_init(t_thread_pool *t_p, t_thread **threads, int id)
{
    *threads = (t_thread *)ft_memalloc(sizeof(t_thread));
    if (!*threads)
        return (-1);
    (*threads)->pool = t_p;
    (*threads)->id = id;
    pthread_create(&(*threads)->pthread, NULL, (void *)thread_do, (*threads));
    pthread_detach((*threads)->pthread);
    return (0);
}

t_thread_pool       *thread_pool_init(int num_threads)
{
    t_thread_pool   *thread_pool;
    int             n;

    g_threads_on_hold = 0;
    g_threads_keepalive = 1;
    assert(num_threads);
    assert(thread_pool = (t_thread_pool *)ft_memalloc(sizeof(t_thread_pool)));
    if (job_queue_init(thread_pool) == -1)
    {
        ft_fprintf(2, "thread_pool_init: Could not allocate memory for job queue\n");
        free(thread_pool);
        return (NULL);
    }
    assert(thread_pool->threads = (t_thread **)ft_memalloc(num_threads * sizeof(t_thread)));
    pthread_mutex_init(&(thread_pool->lock), NULL);
    pthread_cond_init(&thread_pool->all_idle, NULL);
    n = -1;
    while (++n < num_threads)
        thread_init(thread_pool, &thread_pool->threads[n], n);
    while (thread_pool->alive != num_threads)
        ;
    return (thread_pool);
}

int                 thread_pool_add_work(t_thread_pool *thread_pool, void *(*f)(void *), void *data)
{
    t_job           *job;

    job = (t_job *)ft_memalloc(sizeof(t_job));
    assert(job);
    job->task = f;
    job->arg = data;
    pthread_mutex_lock(&thread_pool->queue->rw);
    job_queue_push(thread_pool, job);
    pthread_mutex_unlock(&thread_pool->queue->rw);
    return (0);
}

void                thread_pool_wait(t_thread_pool *thread_pool)
{
    pthread_mutex_lock(&thread_pool->lock);
    while (thread_pool->queue->size || thread_pool->working)
        pthread_cond_wait(&thread_pool->all_idle, &thread_pool->lock);
    pthread_mutex_unlock(&thread_pool->lock);
}

void                thread_pool_destroy(t_thread_pool *thread_pool)
{
    time_t          start, end;
    double          t_passed;
    int             n;
    int             alive_threads;

    if (!thread_pool)
        return ;
    alive_threads = thread_pool->alive;
    t_passed = 0.0;
    time(&start);
    while (t_passed < KILL_THREAD_TIMEOUT && thread_pool->alive)
    {
        semaphore_post_all(thread_pool->queue->has_jobs);
        time(&end);
        t_passed = difftime(end, start);
    }
    while (thread_pool->alive)
    {
        semaphore_post_all(thread_pool->queue->has_jobs);
        sleep(1);
    }
    job_queue_destroy(thread_pool);
    free(thread_pool->queue);
    n = -1;
    while (++n < alive_threads)
        thread_destroy(thread_pool->threads[n]);
    free(thread_pool->threads);
    free(thread_pool);
}

void            thread_pool_pause(t_thread_pool *thread_pool)
{
    int         n;

    n = -1;
    while (++n < thread_pool->alive)
        pthread_kill(thread_pool->threads[n]->pthread, SIGUSR1);
}

void            thread_pool_resume(t_thread_pool *thread_pool)
{
    (void)thread_pool;
    g_threads_on_hold = 0;
}