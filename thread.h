#ifndef THREAD_H
#define THREAD_H

typedef enum            s_thread_status
{
    THREAD_STATUS_IDLE = 0,
    THREAD_STATUS_WORKING
}                       t_thread_status;

typedef struct          s_thread
{
    pthread_t           tid;
    t_thread_status     status;
}                       t_thread;

typedef struct          s_thread_pool
{
    t_thread            pool[RT_THREADS];
}                       t_thread_pool;

#endif