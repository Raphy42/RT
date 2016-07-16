//
// Created by Raphaël Dantzer on 16/07/16.
//

#ifndef RAYTRACER_THREAD_POOL_H
#define RAYTRACER_THREAD_POOL_H

#include <signal.h>
#include <pthread.h>
#include <time.h>

# define KILL_THREAD_TIMEOUT    1.0

static int              g_threads_keepalive;
static int              g_threads_on_hold;

typedef struct          s_semaphore
{
    pthread_mutex_t     mutex;
    pthread_cond_t      cond;
    int                 v;
}                       t_semaphore;

typedef struct          s_job
{
    struct s_job        *prev;
    void                *(*task)(void *);
    void                *arg;
}                       t_job;

typedef struct          s_job_queue
{
    pthread_mutex_t     rw;
    t_job               *first;
    t_job               *last;
    t_semaphore         *has_jobs;
    int                 size;
}                       t_job_queue;

typedef struct s_thread_pool    t_thread_pool;

typedef struct          s_thread
{
    int                 id;
    pthread_t           pthread;
    t_thread_pool       *pool;
}                       t_thread;

struct      s_thread_pool
{
    t_thread            **threads;
    int                 alive;
    int                 working;
    pthread_mutex_t     lock;
    pthread_cond_t      all_idle;
    t_job_queue         *queue;
};

/**
 * SEMAPHORE.c
 */
void    semaphore_wait(t_semaphore *semaphore);
void    semaphore_post_all(t_semaphore *semaphore);
void    semaphore_post(t_semaphore *semaphore);
void    semaphore_reset(t_semaphore *semaphore);
void    semaphore_init(t_semaphore *semaphore, int value);

/**
 * JOB.c
 */
void            job_queue_destroy(t_thread_pool *thread_pool);
int             job_queue_init(t_thread_pool *thread_pool);
t_job           *job_queue_pull(t_thread_pool *thread_pool);
void           job_queue_push(t_thread_pool *thread_pool, t_job *job);

/**
 * THREAD_POOL.c
 */
t_thread_pool       *thread_pool_init(int num_threads);
int                 thread_pool_add_work(t_thread_pool *thread_pool, void *(*f)(void *), void *data);
void            thread_pool_resume(t_thread_pool *thread_pool);
void            thread_pool_pause(t_thread_pool *thread_pool);
void                thread_pool_destroy(t_thread_pool *thread_pool);



#endif //RAYTRACER_THREAD_POOL_H
