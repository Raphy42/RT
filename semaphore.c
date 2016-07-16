//
// Created by Raphaël Dantzer on 16/07/16.
//

#include <assert.h>
#include "thread_pool.h"

void    semaphore_init(t_semaphore *semaphore, int value)
{
    assert(value == 0 || value == 1);
    pthread_mutex_init(&(semaphore->mutex), NULL);
    pthread_cond_init(&(semaphore->cond), NULL);
    semaphore->v = value;
}

void    semaphore_reset(t_semaphore *semaphore)
{
    semaphore_init(semaphore, 0);
}

void    semaphore_post(t_semaphore *semaphore)
{
    pthread_mutex_lock(&semaphore->mutex);
    semaphore->v = 1;
    pthread_cond_signal(&semaphore->cond);
    pthread_mutex_unlock(&semaphore->mutex);
}

void    semaphore_post_all(t_semaphore *semaphore)
{
    pthread_mutex_lock(&semaphore->mutex);
    semaphore->v = 1;
    pthread_cond_broadcast(&semaphore->cond);
    pthread_mutex_unlock(&semaphore->mutex);
}

void    semaphore_wait(t_semaphore *semaphore)
{
    pthread_mutex_lock(&semaphore->mutex);
    while (semaphore->v != 1)
        pthread_cond_wait(&semaphore->cond, &semaphore->mutex);
    semaphore->v = 0;
    pthread_mutex_unlock(&semaphore->mutex);
}